const importObject = {
    imports: { imported_func: (arg) => console.log(arg) },
};  

fetch("simple.wasm")
  .then((response) => response.arrayBuffer())
  .then((bytes) => WebAssembly.instantiate(bytes, importObject))
  .then((results) => {
    results.instance.exports.exported_func();
  });


/** @type {HTMLBodyElement} */
const body = document.getElementById("body");

/** @type {HTMLCanvasElement} */
const canvas = document.getElementById("node-view");
let canvas_width = 0;
let canvas_height = 0;

/** @type {CanvasRenderingContext2D} */
const ctx = canvas.getContext("2d");

const node_color_map = {
    "file": "rebeccapurple",
    "tag": "#006A4E",
    "word": "orange",
}

let node_sprite_size = calc_node_sprite_size(); 
let node_sprite_map = {};
generate_sprite_map();

/** @type {number[][]} - [x, y] */
let coordinates = [];

/** @type {number[][]} - [dx, dy] */
let velocities = []

let x_click_offset = body.getBoundingClientRect().left - canvas.getBoundingClientRect().left;
let x_render_offset = 0;
let y_render_offset = 0;

let simulation_ui_scale = 1;

function scale_graphics() {
    canvas.removeAttribute("width"); canvas.removeAttribute("height");
    const cbr = canvas.getBoundingClientRect()
    let { width, height } = cbr;
    canvas_width = width; canvas_height = height;
    canvas.setAttribute("width", width); canvas.setAttribute("height", height);
    node_sprite_size = calc_node_sprite_size();
    x_click_offset = body.getBoundingClientRect().left - cbr.left;
}

function calc_node_sprite_size() {
    let { width, height } = canvas.getBoundingClientRect();
    return Math.round(((width + height) + 1)/ 2 * .01);
}

/** 
 * @param {number} radius
 * @param {string} color
*/
function create_circle(radius, color) {
   const diameter = radius * 2;
   const oc = new OffscreenCanvas(diameter, diameter);
   let oc_ctx = oc.getContext("2d");
   oc_ctx.beginPath();
   oc_ctx.fillStyle = color;
   oc_ctx.arc(radius, radius, radius, 0, Math.PI*2, true);
   oc_ctx.fill();
   return oc.transferToImageBitmap();
}

function generate_sprite_map() {
    for (const type in node_color_map) {
        node_sprite_map[type] = create_circle(
            node_sprite_size, node_color_map[type]); 
    }
}

/**
 * @param {MouseEvent} event 
 */
function register_node(event) {
    coordinates.push([event.x + x_click_offset - x_render_offset,
        event.y - y_render_offset]);
}

const key_map_pairs = {
    "ArrowUp": "w",
    "ArrowLeft": "a",
    "ArrowDown": "s",
    "ArrowRight": "d",
    "w": "w",
    "a": "a",
    "s": "s",
    "d": "d",
};
let key_mapping = {
    "w": false,
    "a": false,
    "s": false,
    "d": false,
};

/**
 * @param {KeyboardEvent} event
 */
function handle_key(event) {

    let is_key_down = event.type == "keydown";

    key_mapping[key_map_pairs[event.key]] = is_key_down;

    const OFFSET = 10;

    y_render_offset += OFFSET * key_mapping["w"];
    x_render_offset += OFFSET * key_mapping["a"];
    y_render_offset -= OFFSET * key_mapping["s"];
    x_render_offset -= OFFSET * key_mapping["d"];
}

/**
 * @param {WheelEvent} event
 */
function scroll_zoom(event) {

}

window.addEventListener("load", scale_graphics);
window.addEventListener("resize", scale_graphics);
window.addEventListener("click", register_node);
window.addEventListener("keydown", handle_key);
window.addEventListener("keyup", handle_key);
window.addEventListener("wheel", scroll_zoom);

function render() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    ctx.strokeStyle = "white";
    ctx.beginPath();
    for (let i = 0; i < coordinates.length; i++) {
        const x1 = coordinates[i][0] + x_render_offset;
        const y1 = coordinates[i][1] + y_render_offset;
        for (let j = i + 1; j < coordinates.length; j++) {
            const x2 = coordinates[j][0] + x_render_offset;
            const y2 = coordinates[j][1] + y_render_offset;
            ctx.moveTo(x1 + node_sprite_size, y1 + node_sprite_size);
            ctx.lineTo(x2 + node_sprite_size, y2 + node_sprite_size);
            
        }
        ctx.drawImage(node_sprite_map["word"], x1, y1);
    }
    ctx.closePath();
    ctx.stroke();
    requestAnimationFrame(render);
}

requestAnimationFrame(render);
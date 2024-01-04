/** @type {HTMLCanvasElement} */
const canvas = document.getElementById("node-view");

/** @type {CanvasRenderingContext2D} */
const ctx = canvas.getContext("2d");

const node_color_map = {
    "file": "rebeccapurple",
    "tag": "#006A4E",
    "word": "orange",
}

function scale_graphics() {
    canvas.removeAttribute("width");
    canvas.removeAttribute("height");
    let { width, height } = canvas.getBoundingClientRect();
    canvas.setAttribute("width", width);
    canvas.setAttribute("height", height);

    node_sprite_size = calc_node_sprite_size();
}

function calc_node_sprite_size() {
    let { width, height } = canvas.getBoundingClientRect();
    return Math.round((width + height) / 2 * .01);
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
    node_color_map.array.forEach(element => {
        node_sprite_map[element] = create_circle(
            node_sprite_size, node_color_map[element]); 
    });
}

/**
 * @param {MouseEvent} event 
 */
function register_node(event) {
    coordinates.push([event.x, event.y]);
    console.log(`${event.x}, ${event.y}`);
}

window.addEventListener("load", scale_graphics);
window.addEventListener("resize", scale_graphics);
window.addEventListener("click", register_node);

let node_sprite_map = {};
let node_sprite_size = calc_node_sprite_size(); 

/** @type {number[][]} - [x, y] */
let coordinates = [];

/** @type {number[][]} - [dx, dy] */
let velocities = []


function render() {
    ctx.clearRect(canvas.width, canvas.height);
    coordinates.forEach((set) => {
        ctx.drawImage(node_sprite_map["file"], set[0], set[1]);
    });
    requestAnimationFrame(render, 10);
}
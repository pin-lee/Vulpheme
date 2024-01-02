/** largely schemed by Kazani */

/** @type {HTMLCanvasElement} */
const canvas = document.getElementById("node-view");

/** @type {CanvasRenderingContext2D} */
const ctx = canvas.getContext("2d");

function size_canvas() {
    canvas.removeAttribute("width");
    canvas.removeAttribute("height");
    let { width, height } = canvas.getBoundingClientRect();
    canvas.setAttribute("width", width);
    canvas.setAttribute("height", height);
    const node_sprite = create_circle(13, "rebeccapurple");
    ctx.drawImage(node_sprite, canvas.width/2, canvas.height/2);
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

const node_color_map = {
    "file": "rebeccapurple",
    "tag": "#006A4E",
    "word": "orange",
}

const node_sprite_map = {
    "file": create_circle(13, node_color_map.file),
    "tag": create_circle(13, node_color_map.tag),
    "word": create_circle(13, node_color_map.word),
}

window.addEventListener("load", size_canvas);
window.addEventListener("resize", size_canvas);

/** A node exists implicitly */
let nodes = [];

let connections = [];
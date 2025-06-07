const canvas = document.getElementById('grafoCanvas');
const ctx = canvas.getContext('2d');
canvas.width = 1000;
canvas.height = 700;

const btnReproducir = document.getElementById('reproducirBtn');
const imgPersonaje = document.getElementById('personaje'); // 👤 personaje DOM

let nodos = [];
let conexiones = [];
let ruta = [];
let hoverNodo = null;
let pasos = [];
let pasoActual = -1;
let metodoRuta = "dijkstra";
let animacionActiva = false;
let intervaloAnimacion = null;
let nodoObjetivo = null;

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // 🟥 Conexiones normales
    conexiones.forEach(con => {
        const origen = nodos.find(n => n.nombre === con.origen);
        const destino = nodos.find(n => n.nombre === con.destino);
        if (origen && destino) {
            ctx.beginPath();
            ctx.moveTo(origen.x, origen.y);
            ctx.lineTo(destino.x, destino.y);
            ctx.strokeStyle = '#d33';
            ctx.lineWidth = 2;
            ctx.stroke();

            const midX = (origen.x + destino.x) / 2;
            const midY = (origen.y + destino.y) / 2;
            ctx.fillStyle = 'black';
            ctx.font = '12px Arial';
            ctx.fillText(con.peso, midX + 5, midY - 5);
        }
    });

    // 🎯 Ruta resaltada
    const colorMetodo = metodoRuta === "bfs" ? "#00bfff" : metodoRuta === "dfs" ? "#ff7f00" : "#00aa00";
    ruta.forEach((segmento, index) => {
        const origen = nodos.find(n => n.nombre === segmento.origen);
        const destino = nodos.find(n => n.nombre === segmento.destino);
        if (origen && destino) {
            ctx.beginPath();
            ctx.moveTo(origen.x, origen.y);
            ctx.lineTo(destino.x, destino.y);
            ctx.strokeStyle = colorMetodo;
            ctx.lineWidth = 5;
            ctx.stroke();

            if (index === pasoActual - 1) {
                const dx = destino.x - origen.x;
                const dy = destino.y - origen.y;
                const angle = Math.atan2(dy, dx);
                const arrowX = (origen.x + destino.x) / 2;
                const arrowY = (origen.y + destino.y) / 2;

                ctx.beginPath();
                ctx.moveTo(arrowX, arrowY);
                ctx.lineTo(arrowX - 10 * Math.cos(angle - 0.3), arrowY - 10 * Math.sin(angle - 0.3));
                ctx.lineTo(arrowX - 10 * Math.cos(angle + 0.3), arrowY - 10 * Math.sin(angle + 0.3));
                ctx.closePath();
                ctx.fillStyle = 'yellow';
                ctx.fill();
            }
        }
    });

    // 🔵 Nodos
    nodos.forEach(nodo => {
        ctx.beginPath();
        ctx.arc(nodo.x, nodo.y, 6, 0, 2 * Math.PI);

        if (pasoActual >= 0 && nodo.nombre === pasos[pasoActual]) {
            ctx.fillStyle = 'orange';
        } else if (nodo === hoverNodo) {
            ctx.fillStyle = '#33c';
        } else {
            ctx.fillStyle = '#0044cc';
        }

        ctx.fill();

        ctx.font = '12px Arial';
        ctx.lineWidth = 3;
        ctx.strokeStyle = 'white';
        ctx.strokeText(nodo.nombre, nodo.x + 10, nodo.y + 18);
        ctx.fillStyle = 'black';
        ctx.fillText(nodo.nombre, nodo.x + 10, nodo.y + 18);
    });

    // 🎯 Objetivo
    if (nodoObjetivo) {
        ctx.font = "20px Arial";
        ctx.fillStyle = "red";
        ctx.fillText("🏁", nodoObjetivo.x - 10, nodoObjetivo.y - 12);
    }

    // 💬 Tooltip
    if (hoverNodo && hoverNodo.pista) {
        const boxX = hoverNodo.x + 15;
        const boxY = hoverNodo.y - 50;
        const boxWidth = 240;
        const boxHeight = 45;

        ctx.fillStyle = '#ffffcc';
        ctx.strokeStyle = '#333';
        ctx.lineWidth = 1;
        ctx.fillRect(boxX, boxY, boxWidth, boxHeight);
        ctx.strokeRect(boxX, boxY, boxWidth, boxHeight);

        ctx.fillStyle = '#000';
        ctx.font = '12px Arial';
        ctx.fillText("Pista:", boxX + 10, boxY + 15);
        ctx.fillText(hoverNodo.pista, boxX + 10, boxY + 30);
    }
}

// 🧭 Mueve la imagen del personaje
function moverPersonaje(nodo) {
    if (!nodo) return;
    imgPersonaje.style.display = "block";
    imgPersonaje.style.left = `${nodo.x - 16}px`;
    imgPersonaje.style.top = `${nodo.y - 16}px`;
}

function actualizarInfoNodo(nombreNodo, conexiones) {
    const nodo = nodos.find(n => n.nombre === nombreNodo);
    if (!nodo) return;

    const vecinos = conexiones
        .filter(c => c.origen === nombreNodo || c.destino === nombreNodo)
        .map(c => {
            const vecino = c.origen === nombreNodo ? c.destino : c.origen;
            return `${vecino} (${c.peso})`;
        });

    const pista = nodo.pista ? `<p><strong>Pista:</strong> ${nodo.pista}</p>` : "";

    const tipoRuta = metodoRuta.toUpperCase();
    const pesoTotal = ruta.reduce((sum, seg) => {
        const c = conexiones.find(c =>
            (c.origen === seg.origen && c.destino === seg.destino) ||
            (c.origen === seg.destino && c.destino === seg.origen)
        );
        return sum + (c ? c.peso : 0);
    }, 0);

    document.getElementById("infoNodoActual").innerHTML = `
        <p><strong>Nodo actual:</strong> ${nodo.nombre}</p>
        <p><strong>Vecinos:</strong> ${vecinos.join(', ')}</p>
        <p><strong>Tipo de ruta:</strong> ${tipoRuta}</p>
        <p><strong>Peso total:</strong> ${pesoTotal}</p>
        ${pista}
    `;

    mostrarTablaRuta();
    mostrarAnalisisNodo(nodo.nombre);
}

function mostrarTablaRuta() {
    if (!Array.isArray(ruta)) return;
    let tablaHTML = `<table><tr><th>#</th><th>Desde</th><th>Hacia</th><th>Peso</th></tr>`;
    let total = 0;

    ruta.forEach((seg, index) => {
        const c = conexiones.find(c =>
            (c.origen === seg.origen && c.destino === seg.destino) ||
            (c.origen === seg.destino && c.destino === seg.origen)
        );
        const peso = c ? c.peso : 0;
        total += peso;
        const clase = (index === pasoActual - 1) ? " class='resaltado'" : "";
        tablaHTML += `<tr${clase}>
          <td>${index + 1}</td>
          <td>${seg.origen}</td>
          <td>${seg.destino}</td>
          <td>${peso}</td>
        </tr>`;
    });

    tablaHTML += `<tr><td colspan="3"><strong>Total</strong></td><td><strong>${total}</strong></td></tr></table>`;
    document.getElementById("tablaRuta").innerHTML = tablaHTML;
}

function mostrarAnalisisNodo(nombreNodo) {
    const conexionesNodo = conexiones.filter(c => c.origen === nombreNodo || c.destino === nombreNodo);
    let mensaje = "";

    if (conexionesNodo.length >= 4) {
        mensaje = "🔰 Nodo estratégico: Frontera con muchos caminos.";
    } else if (conexionesNodo.length <= 2) {
        mensaje = "⚠️ Cuello de botella: solo tiene 1 o 2 accesos.";
    } else {
        mensaje = "↔ Nodo intermedio con conectividad equilibrada.";
    }

    document.getElementById("analisisNodo").innerHTML = `<p><strong>Análisis:</strong> ${mensaje}</p>`;
}

// ▶ Avanza un paso
function avanzarPaso() {
    pasoActual++;
    if (pasoActual >= pasos.length) {
        pasoActual = 0;
        if (animacionActiva) {
            clearInterval(intervaloAnimacion);
            animacionActiva = false;
            btnReproducir.innerText = '▶ Reproducir recorrido';
        }
    }

    const nodoActual = nodos.find(n => n.nombre === pasos[pasoActual]);
    moverPersonaje(nodoActual);
    draw();
    actualizarInfoNodo(pasos[pasoActual], conexiones);
}

// ▶▶ Reproducir recorrido
function reproducirRuta() {
    if (animacionActiva) {
        clearInterval(intervaloAnimacion);
        animacionActiva = false;
        btnReproducir.innerText = '▶ Reproducir recorrido';
    } else {
        intervaloAnimacion = setInterval(() => avanzarPaso(), 1500);
        animacionActiva = true;
        btnReproducir.innerText = '⏸️ Pausar recorrido';
    }
}

// 🖱 Eventos
canvas.addEventListener('mousemove', (e) => {
    const rect = canvas.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;
    hoverNodo = nodos.find(n => {
        const dx = n.x - x;
        const dy = n.y - y;
        return dx * dx + dy * dy < 100;
    });
    draw();
});

canvas.addEventListener('click', (e) => {
    const rect = canvas.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;
    const nodoClickeado = nodos.find(n => {
        const dx = n.x - x;
        const dy = n.y - y;
        return dx * dx + dy * dy < 100;
    });
    if (nodoClickeado) {
        actualizarInfoNodo(nodoClickeado.nombre, conexiones);
    }
});

// ✅ Inicialización
Promise.all([
    fetch('grafo.json').then(res => res.json()),
    fetch('ruta.json').then(res => res.json()).catch(() => ({ ruta: [], metodo: "dijkstra" }))
])
    .then(([grafoData, rutaData]) => {
        nodos = grafoData.nodos;
        conexiones = grafoData.conexiones;
        ruta = rutaData.ruta || [];
        metodoRuta = rutaData.metodo || "dijkstra";
        pasos = [...new Set(ruta.flatMap(r => [r.origen, r.destino]))];
        if (pasos.length > 0) {
            pasoActual = 0;
            nodoObjetivo = nodos.find(n => n.nombre === pasos[pasos.length - 1]);
            moverPersonaje(nodos.find(n => n.nombre === pasos[0]));
            actualizarInfoNodo(pasos[0], conexiones);
        }
        draw();
    })
    .catch(error => console.error("Error al cargar archivos:", error));

document.getElementById('pasoBtn').addEventListener('click', avanzarPaso);
btnReproducir.addEventListener('click', reproducirRuta);

"use strict";/*Compiled using Cheerp (R) by Leaning Technologies Ltd*/var ay=Math.imul;var az=Math.fround;var oSlot=0;var nullArray=[null];var nullObj={d:nullArray,o:0};function fetchBuffer(p) {var bytes = null;if (typeof window === 'undefined' && typeof self === 'undefined' && typeof require === 'undefined') {bytes = new Promise( (resolve, reject) => {resolve(read(p,'binary'));});} else if (typeof window === 'undefined' && typeof self === 'undefined') {var fs = require('fs');var path = require('path');p = path.join(__dirname, p);bytes = new Promise( (resolve, reject) => {fs.readFile(p, function(error, data) {if(error) reject(error);else resolve(data);});});} else {bytes = fetch(p).then(response => response.arrayBuffer());}return bytes;}function z(f,g){var i=null;i=m(f,g);console.log(i);}function ak(){var f=null,k=null,i=-0.,r=0,l=-0.,av=null;f="glcanvas";f=document.getElementById(f);f=f;q=f;f.height=400;q.width=400;f=q;k="experimental-webgl";f=f.getContext(k);f=f;h=f;f.clearColor(0,0,1,1);f=h.createBuffer();A=f;f=h;i=+f.ARRAY_BUFFER;f.bindBuffer(i,A);k=h;i=+k.ARRAY_BUFFER;r=0;f=aq;f=f;if((r|0)!==0){f=f.subarray((+(r>>>0)));}l=+h.STATIC_DRAW;k.bufferData(i,f,l);S();f=h;k=n;av="a_position";i=+f.getAttribLocation(k,av);f=h;l=+f.FLOAT;f.vertexAttribPointer(i,3,l,!!0,0,0);h.enableVertexAttribArray(i);f=h;i=+f.DEPTH_TEST;f.enable(i);h.viewport(0,0,400,400);}function y(){var f=null,k=0,i=-0.;f=h;k=f.COLOR_BUFFER_BIT;f.clear((+(k|0)));f=h;i=+f.TRIANGLES;f.drawArrays(i,0,3);f=y;+requestAnimationFrame(f);}function S(){var f=null,l=-0.,k=null,i=null;f=h;l=+f.VERTEX_SHADER;f=f.createShader(l);p=f;f=h;l=+f.FRAGMENT_SHADER;f=f.createShader(l);o=f;f=h;k=p;i="attribute vec3 a_position;void main() {\tgl_Position = vec4( a_position.x, a_position.y, a_position.z, 1.0 );}";f.shaderSource(k,i);f=h;k=o;i="void main() {\tgl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );}";f.shaderSource(k,i);h.compileShader(p);h.compileShader(o);f=h.createProgram();n=f;h.attachShader(f,p);h.attachShader(n,o);h.linkProgram(n);h.useProgram(n);}function m(i,j){var k=0,l=0,f=null,r=null;f=String();k=i[j]|0;if((k&255)===0){f=String(f);return f;}else{l=0;}while(1){r=String.fromCharCode(k<<24>>24);f=f.concat(r);l=l+1|0;k=i[j+l|0]|0;if((k&255)!==0){continue;}break;}f=String(f);return f;}var h;var q;var A;var aq=new Float32Array([0,0,0,1,0,0,.5,1,0]);var n;var p;var o;var a=null;var b=null;var c=null;var d=null;var e=null;var __asm=null;var __heap=null;function _asm_z(f){z(a,f);}function aV(){throw new Error('this should be unreachable');};fetchBuffer('Main.wasm').then(r=>WebAssembly.instantiate(r,{i:{y:y,z:_asm_z,ak:ak,}}),console.log).then(r=>{var i=r.instance;a=new Uint8Array(i.exports.aW.buffer);b=new Uint16Array(i.exports.aW.buffer);c=new Int32Array(i.exports.aW.buffer);d=new Float32Array(i.exports.aW.buffer);e=new Float64Array(i.exports.aW.buffer);__asm=i.exports;__heap=i.exports.aW.buffer;i.exports.al();},console.log,console.log);
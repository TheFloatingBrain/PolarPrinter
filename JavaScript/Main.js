"use strict";/*Compiled using Cheerp (R) by Leaning Technologies Ltd*/var bF=Math.imul;var bG=Math.fround;var oSlot=0;var nullArray=[null];var nullObj={d:nullArray,o:0};function fetchBuffer(p) {var bytes = null;if (typeof window === 'undefined' && typeof self === 'undefined' && typeof require === 'undefined') {bytes = new Promise( (resolve, reject) => {resolve(read(p,'binary'));});} else if (typeof window === 'undefined' && typeof self === 'undefined') {var fs = require('fs');var path = require('path');p = path.join(__dirname, p);bytes = new Promise( (resolve, reject) => {fs.readFile(p, function(error, data) {if(error) reject(error);else resolve(data);});});} else {bytes = fetch(p).then(response => response.arrayBuffer());}return bytes;}function al(f,g){var h=null;h=E(f,g);console.log(h);}function ba(o,p,n){var f=null,j=null,h=-0.,m=0,k=-0.,q=null;ak=n;f="glcanvas";f=document.getElementById(f);f=f;T=f;f.height=400;T.width=400;f=T;j="experimental-webgl";f=f.getContext(j);f=f;w=f;f.clearColor(0,0,1,1);f=w.createBuffer();ai=f;f=w;h=+f.ARRAY_BUFFER;f.bindBuffer(h,ai);j=w;h=+j.ARRAY_BUFFER;m=p;f=o;f=f;if((m|0)!==0){f=f.subarray((+(m>>>0)));}k=+w.STATIC_DRAW;j.bufferData(h,f,k);aY();f=w;j=I;q="a_position";h=+f.getAttribLocation(j,q);f=w;k=+f.FLOAT;f.vertexAttribPointer(h,3,k,!!0,0,0);w.enableVertexAttribArray(h);f=w;h=+f.DEPTH_TEST;f.enable(h);w.viewport(0,0,400,400);}function af(){var f=null,j=0,h=-0.;f=w;j=f.COLOR_BUFFER_BIT;f.clear((+(j|0)));f=w;h=+f.TRIANGLES;f.drawArrays(h,0,(+(ak>>>0)));f=af;+requestAnimationFrame(f);}function aY(){var f=null,k=-0.,j=null,h=null;f=w;k=+f.VERTEX_SHADER;f=f.createShader(k);J=f;f=w;k=+f.FRAGMENT_SHADER;f=f.createShader(k);M=f;f=w;j=J;h="attribute vec3 a_position;void main() {\tgl_Position = vec4( a_position.x, a_position.y, a_position.z, 1.0 );}";f.shaderSource(j,h);f=w;j=M;h="void main() {\tgl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );}";f.shaderSource(j,h);w.compileShader(J);w.compileShader(M);f=w.createProgram();I=f;w.attachShader(f,J);w.attachShader(I,M);w.linkProgram(I);w.useProgram(I);}function E(h,i){var j=0,k=0,f=null,m=null;f=String();j=h[i]|0;if((j&255)===0){f=String(f);return f;}else{k=0;}while(1){m=String.fromCharCode(j<<24>>24);f=f.concat(m);k=k+1|0;j=h[i+k|0]|0;if((j&255)!==0){continue;}break;}f=String(f);return f;}var w;var ak;var T;var ai;var I;var J;var M;function b1(bytes){var pages=(bytes+65535)>>16;try{__asm.b3.grow(pages);a=new Uint8Array(__asm.b3.buffer);b=new Uint16Array(__asm.b3.buffer);c=new Int32Array(__asm.b3.buffer);d=new Float32Array(__asm.b3.buffer);e=new Float64Array(__asm.b3.buffer);return pages<<16;}catch(e){return -1;}}var a=null;var b=null;var c=null;var d=null;var e=null;var __asm=null;var __heap=null;function _asm_al(f){al(a,f);}function _asm_ba(o,n){ba(d,o>>2,n);}function b2(){throw new Error('this should be unreachable');};fetchBuffer('Main.wasm').then(r=>WebAssembly.instantiate(r,{i:{af:af,al:_asm_al,ba:_asm_ba,b1:b1,}}),console.log).then(r=>{var i=r.instance;a=new Uint8Array(i.exports.b3.buffer);b=new Uint16Array(i.exports.b3.buffer);c=new Int32Array(i.exports.b3.buffer);d=new Float32Array(i.exports.b3.buffer);e=new Float64Array(i.exports.b3.buffer);__asm=i.exports;__heap=i.exports.b3.buffer;i.exports.bb();},console.log,console.log);
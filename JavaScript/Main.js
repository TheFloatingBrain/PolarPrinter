"use strict";/*Compiled using Cheerp (R) by Leaning Technologies Ltd*/var O=Math.imul;var P=Math.fround;var oSlot=0;var nullArray=[null];var nullObj={d:nullArray,o:0};function fetchBuffer(p) {var bytes = null;if (typeof window === 'undefined' && typeof self === 'undefined' && typeof require === 'undefined') {bytes = new Promise( (resolve, reject) => {resolve(read(p,'binary'));});} else if (typeof window === 'undefined' && typeof self === 'undefined') {var fs = require('fs');var path = require('path');p = path.join(__dirname, p);bytes = new Promise( (resolve, reject) => {fs.readFile(p, function(error, data) {if(error) reject(error);else resolve(data);});});} else {bytes = fetch(p).then(response => response.arrayBuffer());}return bytes;}function p(f,g){var h=null;h=j(f,g);console.log(h);}function C(){var f=null,h=null;f="glcanvas";f=document.getElementById(f);f=f;k=f;f.height=400;k.width=400;f=k;h="experimental-webgl";f=f.getContext(h);f=f;q=f;f.clearColor(0,0,1,1);}function o(){var f=null,h=0;f=q;h=f.COLOR_BUFFER_BIT;f.clear((+(h|0)));f=o;+requestAnimationFrame(f);}function j(l,m){var h=0,i=0,f=null,K=null;f=String();h=l[m]|0;if((h&255)===0){f=String(f);return f;}else{i=0;}while(1){K=String.fromCharCode(h<<24>>24);f=f.concat(K);i=i+1|0;h=l[m+i|0]|0;if((h&255)!==0){continue;}break;}f=String(f);return f;}var q;var k;var a=null;var b=null;var c=null;var d=null;var e=null;var __asm=null;var __heap=null;function _asm_p(f){p(a,f);}function ak(){throw new Error('this should be unreachable');};fetchBuffer('Main.wasm').then(r=>WebAssembly.instantiate(r,{i:{o:o,p:_asm_p,C:C,}}),console.log).then(r=>{var i=r.instance;a=new Uint8Array(i.exports.al.buffer);b=new Uint16Array(i.exports.al.buffer);c=new Int32Array(i.exports.al.buffer);d=new Float32Array(i.exports.al.buffer);e=new Float64Array(i.exports.al.buffer);__asm=i.exports;__heap=i.exports.al.buffer;i.exports.D();},console.log,console.log);
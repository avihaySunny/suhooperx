const reader = require('fs'); 

fs.createReadStream('vuldat.txt'); 
const http = require('http'); 
let app = http.createServer((req, res)=> {
    res.writeHead(200, {'Content-Type': 'text/plain'}); 
    res.end('HelloWorld\n'); 

}); 

app.listen(3000, '127.0.0.1');
console.log('Running port 3000'); 


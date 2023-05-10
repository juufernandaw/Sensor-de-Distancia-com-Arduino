const express = require('express');
const app = express();
const port = 3000;
const distancias = [];
const datas = [];


// Middleware to parse JSON requests
app.use(express.json());

// db contex mongo vai aqui para salvar o que vem do arduino
app.post('/distance', (req, res) => {
  let body = req.body.distance; //conteudo da requisição
  console.log(body);
  // console.log(body.distancia);
  // console.log(body.nome);
  //const {data_hora} = current_datetime = datetime.datetime.now();/
  distancias.push(body);
  //datas.push(data_hora);
  return res.json(distancias);
  
});

// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});

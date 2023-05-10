const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const PORT = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.post('/distance', (req, res) => {
  const { distance } = req.body;
  console.log(`Distância recebida: ${distance}`);
  console.log(req)
  console.log(distance)
  res.send('Distância recebida com sucesso!');
});

app.listen(PORT, () => {
  console.log(`Servidor rodando na porta ${PORT}`);
});
// const express = require('express');
// const app = express();
// const port = 3000;
// const distancias = [];
// const datas = [];
// const distancia = [];

// // Middleware to parse JSON requests
// app.use(express.json());

// // db contex mongo vai aqui para salvar o que vem do arduino
// app.post('/distance', (req, res) => {
//   let body = req.body; //conteudo da requisição
//   console.log(body);
//   // console.log(body.distancia);
//   // console.log(body.nome);
//   //const {data_hora} = current_datetime = datetime.datetime.now();/
//   distancias.push(body);
//   //datas.push(data_hora);
//   return res.json(distancia);
  
// });

// // Start the server
// app.listen(port, () => {
//   console.log(`Server running at http://localhost:${port}`);
// });

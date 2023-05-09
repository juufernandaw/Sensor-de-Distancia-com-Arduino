const express = require('express');
const app = express();
const port = 3000;
const distancias = [];
const datas = [];

// Middleware to parse JSON requests
app.use(express.json());

// GET request to fetch all books
app.get('/books', (req, res) => {
  return res.json(books);
});

// POST request to add a new book
// db contex mongo vai aqui para salvar o que vem do arduino
app.post('/distance', (req, res) => {
  let body = req.body; //conteudo da requisição
  console.log(body.distancia);
  console.log(body.nome);
  //const {data_hora} = current_datetime = datetime.datetime.now();/
  distancias.push(distancia);
  //datas.push(data_hora);
  return res.json(distancias);
  
});


// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});

const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const PORT = 3000;
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
const mongoose = require('mongoose')
const db = `mongodb+srv://ajuliafernanda80:admin@cluster0.ypmssit.mongodb.net/`


// Define the Mongoose schema for your collection
const Schema = mongoose.Schema;
const DistanceSchema = new Schema({
  distance: Number,
  data: Date
});const Distance = mongoose.model('Distance', DistanceSchema);


mongoose.connect(db, {
  useNewUrlParser: true
}).then(() => {
  console.log("MongoDB Conectado!")
}).catch((err) => {
  console.log("Houve um erro ao se conectar ao mongoDB"+err)
})


app.post('/distance', (req, res) => {
  const distance = req.body.distance;
  console.log(`Distância recebida: ${distance}`);
  console.log(distance)
  res.send('Distância recebida com sucesso!');
  if (distance < 100){
    const dataAtual = new Date();
    const timestamp = dataAtual.getTime();
    console.log(timestamp); // Example output: 1659052496123
    //Salvar no BD 
    const newDistance = new Distance({
      distance: req.body.distance,
      data: timestamp // OU datetime.datetime.now()
    }).save().then(() => {
      console.log("Distancia salva com sucesso")
    }).catch((err) => {
      res.status(422).json({ message: 'OCORREU UM ERRO!' })
      console.log("Ocorreu um erro ao salvar a distancia"+err)
    })
    
  } else {
    console.log('Distancia maior que 100')
  }
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

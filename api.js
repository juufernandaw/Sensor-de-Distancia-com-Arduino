const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const PORT = 3000;
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
const mongoose = require('mongoose')
const db = `mongodb+srv://ajuliafernanda80:admin@cluster0.ypmssit.mongodb.net/`


// Define the Mongoose schema
const Schema = mongoose.Schema;
const DistanceSchema = new Schema({
  distance: Number,
  data: Date
});const Distance = mongoose.model('Distance', DistanceSchema);

// Conecta com o BD
mongoose.connect(db, {
  useNewUrlParser: true
}).then(() => {
  console.log("MongoDB Conectado!")
}).catch((err) => {
  console.log("Houve um erro ao se conectar ao mongoDB"+err)
})

// Post do servidor e Mandar para o BD
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
      data: timestamp
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

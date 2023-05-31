import { StatusBar } from 'expo-status-bar';
import { useEffect, useState } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import axios from "axios"

export default function App() {
  //Estado use--> funcao react que cria um estado (estado é: Forma de conseguir mostrar informações dinâmicas na tela , sem estado ele não muda) SÓ ATUALIZA POR SER ESTADO
  //null --> valor inicial da distance por que é um objeto que esta sendo acessado;
  const [distance, setDistance] = useState(null)

  //funcao buscar no servidor
  const fetchDistance = async() => {
    //mesmo ip do arduino *lembrete para o teste.
    // data porque é um atributo que vem do response (get)
    const {data} = await axios.get("http://192.168.100.11:3000/distance")
    setDistance(data[0]) // atualizando o estado
  }
  //Primeira coisa que vai ser rodada assim que entra no app
  useEffect(()=>{
    //setInterval = criando um temporizado para acessar o servidor a cada x milisegundos. chamando o fetch;
    const timer = setInterval(async() => {
      await fetchDistance()
    }, 1000); // tempo que ele vai demorar para buscar no servidor

//funcao para limpar a memoria quando tivesse varias paginas
    return ()=> clearInterval(timer)
  },[])
 
  return (
    <View style={styles.container}>
      <Text>It's a start of something new</Text>
      {
        distance !== null ? ( // não tirar porque a primeira vez rodando é null
          <>
          <Text> Alguém chegou perto! Ultima distancia</Text>
          <Text> {distance.distance} cm! </Text>
          <Text> A data foi: {distance.data}</Text>
          </>
        
        ):(null)
      }
      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});

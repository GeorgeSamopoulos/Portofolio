
import React from "react";
import { BrowserRouter as Router} from "react-router-dom";
import Header from './Header';
import Footer from './Footer';
import Body from './Body'
import './App.css';

function App() {
  return (
    <div id="content">
      
        <Header/>
        <Body/>
        <Footer/>
    </div>
  );
}





export default App;

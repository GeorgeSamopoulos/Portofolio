import React, {useState,useEffect}  from "react";
import logo from './media/ChessScout.jpg';
import { Dropdown } from 'react-bootstrap';
import {SignOut} from './SignOut.js';
import user_icon from './media/icons8-user-32.png';

function Header()  {
    const [signActive,setSignActive]=useState(true);

    useEffect(()=>{
        if(sessionStorage.getItem("Username") && sessionStorage.getItem("Password")){
            setSignActive(false);
        }else{
            setSignActive(true);
        }
    },[]);

    return(
        
            <div id="Header">
                <img id ="chesslogo" src={logo} alt="logo"/>
                {signActive ? null : <Logo/>}
            </div>
    );
}



function Logo () {
    
      return (
        <Dropdown>
            <Dropdown.Toggle variant="light" ><img  src={user_icon}></img></Dropdown.Toggle>
                        
            <Dropdown.Menu>
                <Dropdown.Item onClick={()=>{SignOut()}}>Sign Out</Dropdown.Item>
            </Dropdown.Menu>
        </Dropdown>
      );
    
  }


export default Header;
import {useEffect}from "react";
import  {useNavigate} from "react-router-dom";

function DefaultPage (){

    const nav = useNavigate();
    useEffect(() => {
        console.log('Deafult Sign In');
        nav('/SignIn');
      });
    return;

}

export default DefaultPage;
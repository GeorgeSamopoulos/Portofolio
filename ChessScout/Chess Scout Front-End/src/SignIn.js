import React, {useRef,useState } from "react";
import { BrowserRouter as   Router,Route, Link ,useNavigate, json} from "react-router-dom";



function SignIn(){
    const nav = useNavigate();
    const usernameRef = useRef(null);
    const passwordRef = useRef(null);

    function checkSignIn (input){
        if(Object.keys(input).length === 0){
            window.alert("Incorrect Username or Password");
        }else{
            const user = input[0]['Username'];
            const pass = input[0]['Pass'];
            console.log(user);
            console.log(pass);
            sessionStorage.setItem("Username",user);
            sessionStorage.setItem("Password",pass);
            nav('/HomePage');
            window.location.reload();
        }
        return;
    }

    const handleClickSignIn = () => {
        
        console.log('Check Sign In');

        
        const Username=usernameRef.current.value;
        const Password=passwordRef.current.value;
        

        fetch('https://localhost:7183/api/User/SignIn?username='+Username+'&password='+Password,{headers:{'Content-type':'application/json'}})
        .then(response=>response.json()).then(res => {console.log(res);checkSignIn(res)});
        
    }



    return(
        <div id="LoginComp">
            <div id="LoginContent">
                <div  id="LoginCompForm">
                    <div id="SignInLabel">Sign In</div><br/>
                    <div id="SignInForm" >
                        <label htmlFor="Username">Username</label><br/>
                        <input type="text" id="UsernameSignIn" name="Username" ref={usernameRef}/><br/>
                        
                        <label htmlFor="Password">Password</label><br/>
                        <input type="password" id="PasswordSignIn" name="Password" ref={passwordRef} /><br/>
                        
                            
                        <button id="SignInButton" onClick={handleClickSignIn}  title="Sign In">SIGN IN</button>
                    </div>
                        
                </div>
                <Link to="/SignUp" id="SignInUpButton2"  title="Sign Up">Sign Up?</Link>
            </div>
         
        </div>
    )
    

}




export default SignIn;
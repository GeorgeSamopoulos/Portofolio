import React,{ useState } from "react";
import { BrowserRouter as   Router,useNavigate} from "react-router-dom";
import { CalculateByName } from "./ScoutProfiles.js";


function CreateScoutProfile(){
    const nav = useNavigate();
    const [inputColor, setColor] = useState('');
    const [inputFirstName, setFirstName] = useState('');
    const [inputLastName, setLastName] = useState('');
    
    const handleInputColor = (event) => {
        setColor(event.target.value);
    }

    const handleFirstName = (event) => {
        setFirstName(event.target.value);
    }

    const handleLastName = (event) => {
        setLastName(event.target.value);
    }

    const CreateProfile = () => {

        console.log(inputColor);
        console.log(inputFirstName);
        console.log(inputLastName);

        if(inputColor===""){
            return;
        }
        if(inputFirstName===""){
            return;
        }
        if(inputLastName===""){
            return;
        }
        sessionStorage.removeItem("games");
        sessionStorage.removeItem("preferted_openings_data");
        sessionStorage.removeItem("opening_tree_data");
        sessionStorage.removeItem("PlayerName");
        sessionStorage.removeItem("PlayerElo");
        fetch('https://localhost:7183/CreateProfile?firstname='+inputFirstName+'&lastname='+inputLastName+'&color='+inputColor,{headers:{'Content-type':'application/json'}})
        .then(response=>response.json()).then(res => { CalculateByName(nav); console.log(res);sessionStorage.setItem("games",JSON.stringify(res));})
        var node = document.getElementById("CreateScoutProfile");
        
        node.innerHTML=' <div> <div class="spinner-border" role="status"> <span class="sr-only">Loading...</span> </div></div> ';

    }

    

    return(

        <div id="CreateScoutProfile">
            <div id="CreateScoutProfileComponent">
                <div id="CreateScoutProfileComponentTitle"><div>Create Profile</div></div>
                <div id="CreateScoutProfileComponentForm">
                    <form >
                        <label>Color : </label>
                        <input className="radioColorAny" type="radio" id="AnyChoice" name="ColorCreateProfile" value="Any" checked={inputColor === 'Any'} onChange={handleInputColor} required/>
                        <label htmlFor="WhiteChoice">Any</label>
                        <input className="radioColor" type="radio" id="WhiteChoice" name="ColorCreateProfile" value="White" checked={inputColor === 'White'} onChange={handleInputColor} required/>
                        <label htmlFor="WhiteChoice">White</label>
                        <input className="radioColor" type="radio" id="BlackChoice" name="ColorCreateProfile"  value="Black" checked={inputColor === 'Black'} onChange={handleInputColor} required/>
                        <label htmlFor="BlackChoice">Black</label>
                        <br/>
                        
                        <label htmlFor="AgainstCreateProfile">First Name : </label>&nbsp;
                        <input className="nameInput" type="text" id="AgainstCreateProfile" name="AgainstCreateProfile" onChange={handleFirstName} required/><br/>
                        
                        <label htmlFor="LastNameCreateProfile">Last Name : </label>&nbsp;
                        <input className="nameInput" type="text" id="LastNameCreateProfile" name="LastNameCreateProfile" onChange={handleLastName} required/><br/>
                            
                        <div id="CreateButtonComponent"><button title="Create Profile" type='button' id="CreateButton" onClick={CreateProfile}>Create</button></div>
                    </form>
                </div>
            </div>
        </div>

    );
}

export default CreateScoutProfile;
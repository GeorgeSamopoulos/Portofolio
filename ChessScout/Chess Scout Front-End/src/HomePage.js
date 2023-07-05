import React, { useState } from "react";
import { BrowserRouter as Router, Routes, Route, Link ,useNavigate} from "react-router-dom";
import icon1 from "./media/OpenFolder1.png";
import icon2 from "./media/NewFile.png";
import icon3 from "./media/ChessBoard.png";
import icon4 from "./media/Communication.png";


function HomePage (){
    
    const nav = useNavigate();

    const handleButton1 = () => {
        nav('/OpenProfiles');
        return;
    }

    const handleButton2 = () => {
        nav('/CreateScoutProfile');
        return;
    }

    const handleButton3 = () => {
        nav('/AnalysedGames');
        return;
    }

    const handleButton4 = () => {
        nav('/Communicate');
        return;
    }

    
   
    return (<div id="ContainerHomePage">
                
                <div id="HomePage">
                    <button className="HomePageComponents" onClick={handleButton1} title="Open Scout Profile">
                        <img className="HomePageComponentsIcon" src={icon1} alt=" "/>
                        <div className="HomePageComponentsText">Open Scout Profile</div>
                    </button>
                    <button className="HomePageComponents" onClick={handleButton2} title="Create Scout Profile">
                        <img className="HomePageComponentsIcon" src={icon2} alt=" "/>
                        <div className="HomePageComponentsText">Create Scout Profile</div>
                    </button>
                    <button className="HomePageComponents" onClick={handleButton3} title="Analysed Games">
                        <img className="HomePageComponentsIcon" src={icon3} alt=" "/>
                        <div className="HomePageComponentsText">Your Analysed Games</div>
                    </button>
                    <button className="HomePageComponents" onClick={handleButton4} title="Communicate">
                        <img className="HomePageComponentsIcon" src={icon4} /> 
                        <div className="HomePageComponentsText">Communicate</div>
                    </button>
                </div>
            </div>
            );
    
}



export default HomePage;
import React, { useState , useEffect } from "react";
import mini_chessboard from "./media/mini_chessboard.png";
import delete_icon from './media/x.png';
import { useNavigate } from "react-router-dom";


function AnalysedGames(){

    const nav = useNavigate();
    const [Games,setGames] = useState([]);
    useEffect (()=>{
        sessionStorage.setItem("saveg","true");
        var username = sessionStorage.getItem("Username");
        var password = sessionStorage.getItem("Password");
        fetch('https://localhost:7183/api/User/GetGames?username='+username+'&password='+password,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>{sessionStorage.setItem("SavedGames",res); setGames(res);});
    },[]);
    return (<div>
                <div id = "OpenProfilesTitle"><div>Your Games</div></div>
                <div className="container">
                    <div className="col-md-12 text-center" >
                            <table className="table">
                                <thead>
                                    <tr>
                                        <th>#</th>
                                        <th>White</th>
                                        <th></th>
                                        <th>Black</th>
                                        <th>Result</th>

                                    </tr>
                                </thead>
                                <tbody>
                                    {Games.map((item,index)=>(
                                        <tr>
                                            <td >{index+1}.</td>
                                            <td >{item.White_Player}</td>
                                            <td >vs</td>
                                            <td >{item.Black_Player}</td>
                                            <td >{item.result}</td>

                                            <td >
                                                <button type="button" className = "mini_chessboard_button"  title="Delete Game" onClick = {() => {DeleteGame(item)}}><img src = {delete_icon}></img></button>

                                                <button type="button" className = "mini_chessboard_button"  title="Open Game" onClick = {() => {OpenGame(item,nav)}}><img src = {mini_chessboard}></img></button>
                                            </td>
                                        </tr>
                                    
                                        )
                                    )
                                    }
                                </tbody>
                            </table>

                    </div>
                    </div>
                
           </div>);
    
    
}

async function OpenGame(game,nav){
    var game1 = [];
    var game2 = [];
    game2.push(JSON.stringify(game));
    game1.push(game2);
    await sessionStorage.setItem("gameopen",game1);
    console.log(sessionStorage.getItem("gameopen"));
    nav("/OpenGame");
}

function DeleteGame(game){
    const gid = game.Gid;
    console.log(gid);
    fetch('https://localhost:7183/api/User/DeleteGame?gid='+gid,{headers:{'Content-type':'application/json'}}).then(res=>{if(res.ok){window.alert("Game Deleted Successfully");window.location.reload();}});

    
}

export default AnalysedGames;
import React, { useState , useEffect} from "react";
import { useNavigate } from "react-router-dom"
import delete_icon from './media/x.png';
import scout_profile from './media/scout_profile.png'

function OpenProfiles(){
    const [Profiles,setProfiles]=useState([]);
    let navig = useNavigate();
    useEffect (()=>{
        var username = sessionStorage.getItem("Username");
        var password = sessionStorage.getItem("Password");
        fetch('https://localhost:7183/api/User/GetProfiles?username='+username+'&password='+password,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>setProfiles(res));
    },[]);
    
    return(
        <div>
            <div id = "OpenProfilesTitle"><div>Your Profiles</div></div>
            
                    
                <div className="container">
                    <div className="col-md-12 text-center" >
                        <table className="table">
                            <thead>
                                <tr>
                                <th>#</th>
                                <th>Name</th>
                                <th>Elo Rating</th>
                                </tr>
                            </thead>
                            <tbody>
                                {Profiles.map((item,index)=>(
                                    <tr>
                                        <td >{index+1}.</td>
                                        <td >{item.PlayerName}</td>
                                        <td >{item.Elo}</td>
                                        <td >
                                            <button className="mini_chessboard_button" title="Delete Profile" onClick={()=>{DeleteProfilePid(item.Pid)}}><img src = {delete_icon}></img></button>
                                            <button className="mini_chessboard_button" title="Open Profile" onClick={()=>{OpenProfilePid(item.Pid,navig)}}><img src = {scout_profile}></img></button>
                                        </td>
                                    </tr>
                                
                                    )
                                )
                                }
                            </tbody>
                        </table>

                </div>

            </div>
        </div>
    );
}


function OpenProfilePid(pid,navig){
    fetch('https://localhost:7183/api/CreateProfile/OpenProfile?pid='+pid,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>JSON.stringify(res)).then(res=>setParams(res,navig));
}

function DeleteProfilePid(pid){
    fetch('https://localhost:7183/api/User/DeleteProfiles?pid='+pid,{headers:{'Content-type':'application/json'}}).then(res=>{if(res.ok){window.alert("Game Deleted Successfully");window.location.reload();}}).then(res=>res.json()).then(res=>JSON.stringify(res)).then(res=>sessionStorage.setItem("",res));
}

async function setParams (res,nav){
    res = JSON.parse(res);

    if(res[0] !== null){
        console.log(JSON.stringify(res[0].games));
        await sessionStorage.setItem("games",res[0].games);
        await sessionStorage.setItem("opening_tree_data",res[0].opening_tree_data);
        await sessionStorage.setItem("preferted_openings_data",res[0].preferted_openings_data);
        await sessionStorage.setItem("PlayerName",res[0].PlayerName);
        await sessionStorage.setItem("PlayerElo",res[0].Elo);
        nav("/ScoutProfiles")
    }
    console.log(res[0].Elo);
    console.log(res);


}
export default OpenProfiles;
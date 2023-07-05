import React, { useEffect, useState } from "react"
import searchbtn from "./media/searchbtn.png"
import { useNavigate } from "react-router-dom"
import add_friend from "./media/icons8-add-male-user-32.png"

function SearchUser(){
    const nav = useNavigate();
    const[UserList,setUserList] = useState([]);
    const username = sessionStorage.getItem("Username"); 

    useEffect(()=>{
        var user = JSON.parse(sessionStorage.getItem("searchFriend"));
        setUserList([user]);
    },[]);

    const handlerSearchFriendBar = (nav) => {
        var p = document.getElementById("SearchFriendBar").value;
        var username = sessionStorage.getItem("Username");
        sessionStorage.removeItem("searchFriend");
        setUserList([]);
        fetch('https://localhost:7183/api/User/SearchUsers?username='+username+'&searchFriend='+p,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>sessionStorage.setItem("searchFriend",JSON.stringify(res))).then(res=>window.location.reload());
    }

    return(
        <div id="Communicate">
            <div id="CommunicateComponent">
                <div id="CommunicateComponentTitle">User Search</div>
            </div>
            <div id="CommunicateComponentSearch">
                <div id="SearchFriendBarComponent">
                    <input id="SearchFriendBar" placeholder="Search a new friend"/>
                    <button id="SearchFriendBarBtn" onClick={() => {handlerSearchFriendBar(nav);}}><img src={searchbtn}/></button>
                </div>
            </div>
            
            
            <div id="Friends">   
                <div id="friendsIndex">
                    
                                    
                                        
                                            <table className="table">
                                                <thead>
                                                    <tr>
                                                        <th>#</th>
                                                        <th>Username</th>
                                                        <th></th>

                                                    </tr>

                                                </thead>
                                            <tbody>
                                            {UserList.length === 0 ? null:(
                                                 UserList.map((item,index)=>(
                                                <tr>
                                                    <td className="">{index+1}.</td>
                                                    <td className="">{item.Username}</td>
                                                    <td className=""><button onClick={()=>{handlerSendRequest(username,item.Username)}} className="friendsButton" title="Send Friend Request"><img src = {add_friend}></img></button></td>
                                                </tr>)))
                                            }
                                            </tbody>
                                            </table>
                                        
                                       
                                    
                </div>
            </div>
        </div>
    );
}

const handlerSendRequest = (sender,receiver) =>{
    fetch('https://localhost:7183/api/User/CreateRequest?Sender='+sender+'&Receiver='+receiver,{headers:{'Content-type':'application/json'}}).then(res=>{console.log("create successful");}).then(res=>{window.location.reload();});
    window.location.reload();
    
}



export default SearchUser;
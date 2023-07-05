import React, { useEffect, useState } from "react"
import searchbtn from "./media/searchbtn.png"
import { useNavigate } from "react-router-dom";
import delete_icon from './media/x.png';
import open_chat_icon from './media/icons8-chat-32.png';
import accept_icon from './media/icons8-add-male-user-32.png';


function Communicate(){
    const nav = useNavigate();
    const[friendsList,setFriendList] = useState([]);
    const[requestList,setRequestList] = useState([]);

    useEffect(()=>{
        const username = sessionStorage.getItem("Username");
        const password = sessionStorage.getItem("Password");
        fetch('https://localhost:7183/api/User/GetFriendRequests?username='+username,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>{setRequestList(res);console.log(res);});
        fetch('https://localhost:7183/api/User/GetFriends?username='+username+'&password='+password,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>{setFriendList(res);console.log(res);});

    },[]);

    
    return(
        <div id="Communicate">
            <div id="CommunicateComponent">
                <div id="CommunicateComponentTitle">Your Friends</div>
            </div>
            <div id="CommunicateComponentSearch">
                <div id="SearchFriendBarComponent">
                    <input id="SearchFriendBar" placeholder="Search a new friend"/>
                    <button id="SearchFriendBarBtn" onClick={() => {handlerSearchFriendBar(nav);}}><img src={searchbtn}/></button>
                </div>
            </div>
            
            <div class="container">
                <div class="row">
                    <div className="col-sm-4" >
                        
                            <h3>Friends</h3>
                            <table className="table tableFriends">
                                <thead>
                                    <tr>
                                        <th>User</th>
                                    </tr>
                                </thead>
                                <tbody >
                                {
                                    
                                    friendsList.map((item,index)=>(
                                                
                                            <tr key = {index} className="friendComponent">
                                                    
                                                    <td  className="friendsUsername">{item.username}</td>
                                                    <td >
                                                        <button className="friendsButton" onClick={()=>{handlerDeleteFriend(item.username)}} title="Delete Friend"><img src = {delete_icon}></img></button>
                                                        
                                                    </td>
                                                    <td><button onClick={()=>{handlerOpenChat(nav,item.username,item.uid)}} title="Open Chat"><img src = {open_chat_icon}></img></button></td>
                                                    

                                            </tr>     
                                                
                                                
                                        )

                                    ) 
                                }
                                </tbody>
                            </table>
                    </div>
                    <div className="col-sm-3" ></div>
                    <div className="col-sm-4">
                    <h3>Requests</h3>
                            <table className="table tableFriends">
                                <thead>
                                    <th>User</th>
                                </thead>
                                <tbody className="friendComponent">
                                    {    requestList.map((item,index)=>(
                                                
                                                <tr key = {index} className="friendComponent">
                                                        <td className="friendsUsername">{item.Sender}</td>
                                                        <td><button className="friendsButton" onClick={()=>{handlerDeleteRequest(item.SenderUid,item.ReceiverUid)}}><img src = {delete_icon}></img></button></td>
                                                        <td><button className="friendsButton" onClick={()=>{handlerAcceptRequest(item.SenderUid,item.ReceiverUid)}}><img src = {accept_icon}></img></button></td>
                                                                
                                                </tr>     
                                                    
                                                    
                                            )

                                        ) }
                                </tbody>
                            </table>
                    </div>
                </div>
            </div>
        </div>
    );
}

const handlerOpenChat = (nav,username,uid)=>{

    sessionStorage.setItem("ChatWith",username);
    sessionStorage.setItem("ChatWithUid",uid);
    nav('/OpenChat');

}

const handlerDeleteFriend = (username)=>{

    const user = sessionStorage.getItem("Username");
    fetch('https://localhost:7183/api/User/DeleteFriend?username1='+username+'&username2='+user,{headers:{'Content-type':'application/json'}}).then(res=>{console.log("deleted successfully")});
    window.location.reload();
}

const handlerSearchFriendBar = (nav) => {
    var p = document.getElementById("SearchFriendBar").value;
    var username = sessionStorage.getItem("Username");
    fetch('https://localhost:7183/api/User/SearchUsers?username='+username+'&searchFriend='+p,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>sessionStorage.setItem("searchFriend",JSON.stringify(res))).then(res=>nav('/SearchUser'));
}


const handlerDeleteRequest = (SenderUid,ReceiverUid) => {
    fetch('https://localhost:7183/api/User/DeleteRequest?SenderUid='+SenderUid+'&ReceiverUid='+ReceiverUid,{headers:{'Content-type':'application/json'}}).then(res=>{console.log("delete successful");}).then(res=>{window.location.reload();});
    window.location.reload();
}

const handlerAcceptRequest = (SenderUid,ReceiverUid) => {
    fetch('https://localhost:7183/api/User/AcceptRequest?SenderUid='+SenderUid+'&ReceiverUid='+ReceiverUid,{headers:{'Content-type':'application/json'}}).then(res=>{console.log("accept successful")}).then(window.location.reload());
    window.location.reload();

    
}


export default Communicate;
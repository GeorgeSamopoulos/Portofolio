import React, { useEffect, useState } from "react"
import searchbtn from "./media/searchbtn.png"
import { useNavigate } from "react-router-dom";


function OpenChat(){



    const [messages,setMessages] = useState([]);
    const [usernameChatWith,setUsernameChatWith] = useState(sessionStorage.getItem("ChatWith"));
    useEffect(()=>{
        const intervalId = setInterval(() => {
            console.log("open chat");
            const receiver = sessionStorage.getItem("ChatWith");
            const sender = sessionStorage.getItem("Username");
            fetch('https://localhost:7183/api/User/GetMessages?Sender='+sender+'&Receiver='+receiver,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>setMessages(res));

      
            
          }, 5000); 
      
          return () => {
            clearInterval(intervalId);
          };
       
    },[]
    )

    const [chatWithUid,setChatWithUid] = useState(parseInt(sessionStorage.getItem("ChatWithUid")));
    const [inputValue, setInputValue] = useState('');

    const handleInputChange = (event) => {   
      setInputValue(event.target.value);
    };

    const SendMessage = (message) => {
        setInputValue('');
        const receiver = sessionStorage.getItem("ChatWith");
        const sender = sessionStorage.getItem("Username");
        fetch('https://localhost:7183/api/User/SendMessage?Sender='+sender+'&Receiver='+receiver+"&MessageText="+message,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>console.log("messgae send"));
    };

    
    return (
        <>
            <div id="ChatUser"> <div>{usernameChatWith}</div></div>
            <div className="container" id="ChatContainer">
                <div className="chat-container" id="ChatComponent">
                    <div className="chat-messages ChatElements">
                    
                        {messages.map((msg, index) => (
                                
                            (msg.UidSender === chatWithUid) ?  
                                <div key={index} className="message user MessageReceive">
                                    {msg.MessageText } 
                                </div>
                                :
                                <div key={index} className="message user MessageSend">
                                    {msg.MessageText} 
                                </div>
                                
                        ))}
                    
                    </div>
                    <div className="chat-input ">
                    <input
                        className="ChatInput"
                        type="text"
                        value = {inputValue}
                        placeholder="Type your message"
                        onChange={handleInputChange}
                    />
                    <button className="btn btn-primary " onClick={()=>{SendMessage(inputValue)}}>
                        Send
                    </button>
                    </div>
                </div>
            </div>
        </>         
    );
    

}


export default OpenChat;
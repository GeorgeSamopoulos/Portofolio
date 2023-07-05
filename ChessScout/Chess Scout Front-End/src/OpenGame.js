import 'bootstrap/dist/css/bootstrap.min.css';
import React, { useState, useEffect } from 'react';
import {Chessboard} from 'react-chessboard';
import {Chess} from 'chess.js';
import forward from './media/icons8-chevron-right-32.png'
import end from './media/icons8-end-32.png'
import start from './media/icons8-start-32.png'
import back from './media/icons8-chevron-left-32.png'


var currmove = 0;
var movesLength ;
function ChessBoard() {
    const [game, setGame] = useState(new Chess());
    const [result, setResult] = useState();
    const [White_Player , setWhitePlayer] = useState();
    const [Black_Player , setBlackPlayer] = useState();
    const [pgn_load,setPgn] = useState();
    const [moves,setMoves] = useState([]);
    const [activeMove,setActiveMove] = useState(0);
    const ChangePosition = (fen) => { setGame (new Chess(fen)) };

    useEffect(()=>{
        var game_details = JSON.parse(sessionStorage.getItem("gameopen"))[0];
        if(sessionStorage.getItem("saveg")==="true"){
            game_details = sessionStorage.getItem("gameopen");
            game_details = JSON.parse(game_details);
            const myString = game_details.Game;
            var replacedString = myString.replace(/\]/g, "]\n");
            replacedString = replacedString.replace("\n1","\n\n1");
            game_details.Game = replacedString;
            
            // sessionStorage.removeItem("saveg");
        }
        console.log(game_details);
        game.loadPgn(game_details.Game);
        const moveList = game.history({ verbose: true });
        ChangePosition();
        setMoves(moveList);
        movesLength = moves.length;
        setWhitePlayer(game_details.White_Player);
        setBlackPlayer(game_details.Black_Player);
        setResult(game_details.result);
        setPgn(game_details.Game);
        console.log("game changed");

        const handleKeyPress = (event) => {
            console.log(event.key);
            if(event.key === 'ArrowRight'){
                console.log("right");
                handleMoveButtonClick(currmove+1);
            }else if(event.key === 'ArrowLeft'){
                console.log("left");
                handleMoveButtonClick(currmove-1);
            }
            
        };
      
          window.addEventListener('keydown', handleKeyPress);
      
          return () => {
            window.removeEventListener('keydown', handleKeyPress);
          };
    },[]
    );

    const handleMoveButtonClick = (number) => {
        if(moves.length<=number){
        
            return;
        }
        if(number === -1 ){
            var chessboard = new Chess();
            const fen = chessboard.fen();
            ChangePosition(fen);
        }
        
        if(0 > number){
        console.log(number);

            return;
        }
        setActiveMove(number);
        currmove = number;

        var chessboard = new Chess();
        for(var i=0;i<=number;i++){
            chessboard.move(moves[i]);
        }
        const fen = chessboard.fen();
        ChangePosition(fen);
    }

    function SaveGame  () {
        console.log("ok");
        fetch('https://localhost:7183/api/User/SaveGame?username='+sessionStorage.getItem("Username")+'&white='+White_Player+'&black='+Black_Player+'&result='+result+'&game='+pgn_load,{headers:{'Content-type':'application/json'}}).then(res=>{if(res.ok){window.alert("Game Saved Successfully")}});
    }

    return (
        <div id="OpenGame" >
            
            <div className="container">
                <div className="row">
                    <div className="col">
                        <div id="chessboard">
                            <Chessboard id="BasicBoard"  position={game.fen()}/>
                        </div>

                    </div>
                    <div className="col">

                        <div id="GameInfo"><span  className="GameNames" >{White_Player} - {Black_Player}</span><span className="GameResult">{result}</span></div>
                        {
                            moves.map((move,index)=>(
                                
                                <span className={index % 2 === 0 ? `moveLabel` : ''}><label>{index % 2 === 0 ? `${index/2 + 1}.` : ''}</label><button className={activeMove === index ? "activeButtonStyle" : "inactiveButtonStyle"} onClick={()=>handleMoveButtonClick(index)}>{move.san}</button></span>
                                
                                )
                                )
                            }
                        <span className="moveLabel">{result}</span>
                        <div id="controlButtons">
                            <button className='controlButton'  title="Start" onClick={() => handleMoveButtonClick(-1)}><img src={start}/></button>
                            <button className='controlButton' title="Back" onClick={() => handleMoveButtonClick(activeMove-1)}><img src={back}/></button>
                            <button className='controlButton' title="Next" onClick={() => handleMoveButtonClick(activeMove+1)}><img src={forward}/></button>
                            <button className='controlButton' title="End" onClick={() => handleMoveButtonClick(moves.length-1)}><img src={end}/></button>
                        </div>
                        <div id="SaveShareOptions">
                            <button onClick={() => SaveGame()} title="Save Game" className="buttonsOpenGame">Save Game</button>
                            
                        </div>
                    </div>
                </div>
            </div>
        </div>
     );
     
     
}
    
    
    



export default ChessBoard;
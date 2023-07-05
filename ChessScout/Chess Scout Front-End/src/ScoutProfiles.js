import React, { useEffect,useState } from "react";
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import { BrowserRouter as   Router,useNavigate} from "react-router-dom";
import { Container, Row, Col,Table } from 'react-bootstrap';
import mini_chessboard from "./media/mini_chessboard.png";


const GetData = (nav) =>{
    fetch('https://localhost:7183/GetData',{
        headers:{'Content-type':'application/json'}
    }).then(response => response.json()).then(data => {
            sessionStorage.setItem("PlayerName",data.name);
            sessionStorage.setItem("PlayerElo",data.elo);
            sessionStorage.setItem("PlayerLastYear",data.lastYear);
            sessionStorage.setItem("PlayerStartYear",data.startYear);
        }
    ).then(res => {nav('/ScoutProfiles');});

}

var data=[];
var preferted_openings_data=[];
var name;
var elo;

function ScoutProfiles(){
    
    var [displayComp, setDisplayComp] = useState(12);
    var [depth,setDepth] = useState(0);
    var [opening_cout, setOpeningCount] = useState(6);
    var [opening_tree_data , setOpeningTreeData] = useState([]);
    var [NumOfDownloaded,setNumOfDownloaded] = useState(8);
    let nav = useNavigate();
    useEffect(()=>{
        const fetchData = async () => {
            try {
              const response = await fetch('https://localhost:7183/CalculateByMove?depth='+depth,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>JSON.stringify(res)).then(res=>sessionStorage.setItem("opening_tree_data",res));
              opening_tree_data =  sessionStorage.getItem("opening_tree_data");
              opening_tree_data = JSON.parse(opening_tree_data);
              console.log(opening_tree_data);
              setNumOfDownloaded(opening_tree_data.NumOfDownloaded);
              opening_tree_data = opening_tree_data.datamoves;
              setOpeningTreeData(opening_tree_data);
            } catch (error) {
              // Handle error
              console.error(error);
            }
          };
      
          const fetchRepeatedly = async () => {
            var flag = true;
            while (flag) {
              await fetchData();
              await new Promise(resolve => setTimeout(resolve, 5000)); // Wait for 30 seconds
              flag = check_games();
            }
          };

          function check_games ()  {
                
                if(opening_tree_data === null){
                    return true;
                }else{
                    var temp =  sessionStorage.getItem("opening_tree_data");
                    temp = JSON.parse(temp);

                    if(temp.NumOfDownloaded < data.length){
                        return true;
                    }else{

                        return false;
                    }
                }
          }

          fetchRepeatedly();
          return () => {
            // Stop the repeated fetch if necessary
          }
    },[])

    const CalculateByMoveDepth =(Opening_Tree_Last_Move)=>{
        try {
            
            const response = fetch('https://localhost:7183/CalculateByMove?depth='+depth+'&last_move='+Opening_Tree_Last_Move,{headers:{'Content-type':'application/json'}}).then(res=>res.json()).then(res=>JSON.stringify(res)).then(res=>sessionStorage.setItem("opening_tree_data",res));
            opening_tree_data =  sessionStorage.getItem("opening_tree_data");
            opening_tree_data = JSON.parse(opening_tree_data);
            console.log(opening_tree_data);
            setNumOfDownloaded(opening_tree_data.NumOfDownloaded);
            opening_tree_data = setOpeningTreeData(opening_tree_data.datamoves);
            setOpeningTreeData(opening_tree_data);
          } catch (error) {
            console.error(error);
          }
    };

        data = sessionStorage.getItem("games");
        opening_tree_data =  sessionStorage.getItem("opening_tree_data");
        preferted_openings_data =  sessionStorage.getItem("preferted_openings_data");
        name = sessionStorage.getItem("PlayerName");
        elo = sessionStorage.getItem("PlayerElo");
        data = JSON.parse(data);
        preferted_openings_data = JSON.parse(preferted_openings_data);
        console.log(data);
        console.log(preferted_openings_data);
        opening_tree_data = JSON.parse(opening_tree_data);
        opening_tree_data = opening_tree_data.datamoves;
        

    if(data !== null && opening_tree_data !== null && preferted_openings_data !== null && elo !== null && name !== null){
        return(
            <div>
                    <div id="PlayerId">
                        
                        <div id="ScoutProfileName">
                            {sessionStorage.getItem("PlayerName")}
                        </div>&ensp;
                        <div id="ScoutProfileElo">
                            (ELO : {sessionStorage.getItem("PlayerElo")})
                        </div> 

                    </div>
                    <div id="ProfileFilters">
                        <div id="filterParams">
                        
                                <label className="filterParams">
                                    Color <br/>
                                    <select id="colors" >
                                        <option value="any" selected>Any</option>
                                        <option value="White">White</option>
                                        <option value="Black">Black</option>
                                    </select> 
                                </label>
                                <label className="filterParam">
                                    from <br/>
                                    <input type="number"  id="inputfrom"  min={sessionStorage.getItem("PlayerStartYear")} max={sessionStorage.getItem("PlayerLastYear")} />
                                </label>
                                <label className="filterParam">
                                    to <br/>
                                    <input type="number"  id="inputto"  min={sessionStorage.getItem("PlayerStartYear")} max={sessionStorage.getItem("PlayerLastYear")}/>
                                </label>
                                <button className="filterParamButton" type="button" value="Submit" title="Change Filters" onClick={ChangeFilters}> Change </button>
                            
                            
                        </div>
                    </div>
                    <Container >
                        <Row id = "ContainerScoutProfile">
                            <Col md='6'>
                                <div className="TilesComp">
                                    <label className="Tiles">Games ({data.length})</label>
                                </div>
                                {displayComp < data.length ? 
                                
                                createDivs(data,displayComp,nav)
                                :(data.map((item,index)=>(
                                    <div className="GameComp" key={index}>
                                        <div className="GamePresent" key={index}>
                                            <div>{index+1}.</div>
                                            <div>{item.White_Player} vs {item.Black_Player}</div>
                                            <div>{item.result}</div>
                                            <div>{item.ECO}</div>
                                            <div>{item.year}</div>
                                            <button type="button" className = "mini_chessboard_button" title="Open Game" onClick = {() => OpenGame(item.Gid,nav)}><img src = {mini_chessboard}></img></button>
                                        </div></div>
                                        )
                                    ))
                                }
                                    
                                
                                { displayComp < data.length ? <button className="" onClick = {()=>{setDisplayComp(displayComp + 12)}}>More</button> : <div></div>}
                            </Col>
                            <Col md='6'> 
                                <div>
                                    <div className="TilesComp">
                                        <label className="Tiles">Preferted Opening</label>
                                    </div>
                                    <Table bordered hover size="sm">
                                        <thead>
                                            <tr>
                                                <th>ECO</th>
                                                <th>Opening Name</th>
                                                <th>Games</th>
                                                <th>W.rate</th>
                                            </tr>
                                        </thead>
                                        <tbody>
                                            {   opening_cout < preferted_openings_data.length?

                                                opening_table(preferted_openings_data,opening_cout)
                                                :(preferted_openings_data.map((item,index)=>(
                                                    <tr key={index}>
                                                        <td>{item.ECO}</td>
                                                        <td>{item.Name}</td>
                                                        <td>{item.PRate}%</td>
                                                        <td>{item.WRate}%</td>
                                                    </tr>
                                                )
                                                ))
                                            }
                                        </tbody>
                                        { opening_cout < preferted_openings_data.length ? <button className="" onClick = {()=>{setOpeningCount(opening_cout + 6)}}>More</button> : <div></div>}

                                    </Table>
                                </div>
                                <div>
                                    <div className="TilesComp">
                                        <label className="Tiles">Opening Tree ({NumOfDownloaded} out of {data.length})</label>
                                    </div>
                                    <Table bordered hover size="sm">
                                        <thead>
                                            <tr>
                                                <th>Moves</th>
                                                <th>P.rate</th>
                                                <th>W.rate</th>
                                                <th>Games</th>
                                                <th>In</th>
                                            </tr>
                                        </thead>
                                        <tbody>
                                            
                                            {
                                                    (opening_tree_data.map((item,index)=>(
                                                    <tr key={index}>
                                                        <td>{item.Move}</td>
                                                        <td>{((item.PRate).toFixed(2))*100}%</td>
                                                        <td>{((item.WRate).toFixed(2))*100}%</td>
                                                        <td>{item.Move}</td>
                                                        <td><button onClick={()=>{setDepth(depth+1);CalculateByMoveDepth(item.Move);}}>follow</button></td>
                                                    </tr>
                                                    )
                                                    ))
                                                }
                                            
                                        </tbody>
                                    </Table>
                                </div>

                                <span id="ViewGraphsComp">
                                    <button  id = "ViewGraphsButton" title="View Graphs" onClick={()=>{nav("/ViewGraphs")}}>View Graphs</button>
                                    <button  id = "ViewGraphsButton" title="Save Profile" onClick={()=>{saveScoutProfile()}}>Save Scout Profile</button>

                                </span>
                            </Col >
                        </Row>
                    </Container>
                </div>
                );
            }
}
        
function OpenGame (gid,nav) {
    console.log(gid);
    fetch('https://localhost:7183/DownloadGame?gid='+gid,{
        headers:{'Content-type':'application/json'}
    }).then(res=>res.json(res)).then(res=>JSON.stringify(res)).then(res=>{sessionStorage.setItem("gameopen",res);}).then(res=>sessionStorage.setItem("saveg","false")).then(res=>{nav("/OpenGame");});
}

const ChangeFilters = () => {

        var from = document.getElementById('inputfrom').value;
        var to = document.getElementById('inputto').value;
        var inputColor = document.getElementById('colors').value;

        if(from >= to){
            alert("Wrong Filter Apply");
        }

        if(from!==null && to!==null){
            console.log(inputColor);
            console.log(from);
            console.log(to);
            fetch('https://localhost:7183/NewFilters?lastyear='+to+'&startyear='+from+'&color='+inputColor,{
                headers:{'Content-type':'application/json'}
            }).then(response => response.json()).then(data => {

                    CalculateByNameFilter();
                    sessionStorage.setItem("games",JSON.stringify(data));
                }
            );

        }
        
}
function CalculateByNameFilter(){
    fetch('https://localhost:7183/CalculateNewFiltersByName',{
        headers:{'Content-type':'application/json'}
    })
    .then(results => results.json()).then(res=>JSON.stringify(res)).then(res=>sessionStorage.setItem("preferted_openings_data",res)).then(res=>window.location.reload());
    

}    



export function CalculateByName (nav) {
    fetch('https://localhost:7183/CalculateByName',{headers:{'Content-type':'application/json'}}).then(results => results.json()).then(res=>{console.log(res);sessionStorage.setItem("preferted_openings_data",JSON.stringify(res))}).then(CalculateByMove(nav));
    
    
}

function CalculateByMove (nav){
    fetch('https://localhost:7183/CalculateByMove?depth=0',{headers:{'Content-type':'application/json'}}).then(results => results.json()).then(res=>JSON.stringify(res)).then(res=> sessionStorage.setItem("opening_tree_data",res)).then(res=>{GetData(nav)});

}

function createDivs (data,size,nav){
    var divs = [];
    for(let i =0 ; i<size ; i++){
        divs.push(data[i]);
    }


    return <>{
            divs.map((item,index)=>(
                                    <div className="GameComp" key={index}>
                                        <div className="GamePresent" key={index}>
                                            <div>{index+1}.</div>
                                            <div>{item.White_Player} vs {item.Black_Player}</div>
                                            <div>{item.result}</div>
                                            <div>{item.ECO}</div>
                                            <div>{item.year}</div>
                                            <button type="button" className = "mini_chessboard_button"  onClick = {() => OpenGame(item.Gid,nav)}><img src = {mini_chessboard}></img></button>
                                        </div></div>
                                        )
                                    )
            }
        </>;
}

function opening_table(data,size){
    const divs = [];
    for(let i =0 ; i<size ; i++){
        var item = data[i];
        divs.push(
            <tr key={i}>
                <td>{item.ECO}</td>
                <td>{item.Name}</td>
                <td>{item.PRate}%</td>
                <td>{item.WRate}%</td>
            </tr>
            
        );
    }
    return divs;

}

function saveScoutProfile(){
    const username = sessionStorage.getItem("Username");
    const playername = sessionStorage.getItem("PlayerName");
    const elo = sessionStorage.getItem("PlayerElo");
    const opening_tree_data =  sessionStorage.getItem("opening_tree_data");
    const preferted_openings_data =  sessionStorage.getItem("preferted_openings_data");
    const games = sessionStorage.getItem("games");

    console.log(username);
    console.log(playername);
    console.log(elo);
    console.log(preferted_openings_data);
    console.log(games);
    console.log(opening_tree_data);



    axios.post('https://localhost:7183/api/User/SaveProfile',
        {
            PlayerName:playername,
            UserName:username,
            Elo:elo,
            preferted_openings_data : preferted_openings_data,
            games:games,
            opening_tree_data:opening_tree_data
        }
    
    ).then(res => {window.alert("Profile Saved Successfully");}); 
    return; 
}




export default ScoutProfiles;
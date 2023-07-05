import React , { useEffect } from "react";
import { BrowserRouter as  Router,Routes, Route, Link} from "react-router-dom";
import SignIn from "./SignIn";
import SignUp from "./SignUp";
import HomePage from "./HomePage";
import DefaultPage from "./DefaultPage";
import OpenProfiles from"./OpenProfiles";
import CreateScoutProfile from "./CreateScoutProfile";
import ScoutProfiles from "./ScoutProfiles";
import AnalysedGames from"./AnalysedGames";
import Communicate from"./Communicate";
import ChessBoard from "./OpenGame";
import ViewGraphs from "./ViewGraphs";
import SearchUser from "./SearchUser";
import OpenChat from "./OpenChat"



function Body(){

    return(
        <StartPage/>    
    )


}

function StartPage(){
   
    

    return(
        
               <Router>
                    
                    <Routes>
                        <Route path="/" element={<DefaultPage/>}/>
                        
                        <Route path="/SignIn" element={<SignIn/>}/>
                
                        <Route path="/SignUp" element={<SignUp/>} />

                        <Route path="/HomePage" element={<HomePage/>}/>

                        <Route path="/CreateScoutProfile" element={<CreateScoutProfile/>}/>
                        
                        <Route path="/ScoutProfiles" element={<ScoutProfiles/>}/>

                        <Route path="/AnalysedGames" element={<AnalysedGames/>}/>

                        <Route path="/Communicate" element={<Communicate/>}/>

                        <Route path="/OpenProfiles" element={<OpenProfiles/>}/>

                        <Route path="/OpenGame" element={<ChessBoard/>}/>

                        <Route path="/ViewGraphs" element={<ViewGraphs/>}></Route>

                        <Route path="/SearchUser" element={<SearchUser/>}></Route>

                        <Route path="/OpenChat" element={<OpenChat/>}></Route>
                    </Routes>


                </Router> 
                
                    
            
            
            
        
    )
}






export default Body
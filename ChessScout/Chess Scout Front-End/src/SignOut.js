import React, {useState,}  from "react";
export function SignOut(){
    window.location.href='http://localhost:3000/SignIn';
    sessionStorage.removeItem("Username");
    sessionStorage.removeItem("Password");
}

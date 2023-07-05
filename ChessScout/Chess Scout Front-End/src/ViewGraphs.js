import React, { useState } from 'react';
import { Bar } from 'react-chartjs-2';
import Chart from 'chart.js/auto';
import { useEffect } from 'react';




function ChartComponent () { 

    const data = {
        labels: [],
        datasets: [
            {
            label: 'Sales',
            data: [],
            backgroundColor: 'rgba(255, 99, 132, 0.2)',
            borderColor: 'rgba(255, 99, 132, 1)',
            borderWidth: 1,
            },
        ],
    };

    const options = {
        scales: {
            yAxes: [
                {
                    ticks: {
                        beginAtZero: true,
                    },
                },
            ],
        },
    };
    const [dataNumbersPlayed,setDataNumbersPlayed] = useState(data);
    const [dataOptionsPlayed,setDataOptionsPlayed] = useState(options);
    const [dataNumbersWin,setDataNumbersWin] = useState(data);
    const [dataOptionsWin,setDataOptionsWin] = useState(options);
    
    useEffect(() => {
        var op =  JSON.parse(sessionStorage.getItem("preferted_openings_data"));
        var numb = [];
        var labels = [];
        for(let i = 0 ; i < op.length ; i++){
            numb.push((op[i].PRate));
            labels.push(op[i].Name);
        }


        //------------ Played ------------
        const data = {
            labels: labels,
            datasets: [
                {
                label: 'Preference in %',
                data: numb,
                backgroundColor: 'rgba(102, 178, 255, 1)',
                borderColor: 'rgba(102, 178, 255, 1)',
                borderWidth: 1,
                },
            ],
        };
        setDataNumbersPlayed(data);
        const options = {
            scales: {
                yAxes: [
                    {
                        ticks: {
                            beginAtZero: true,
                        },
                    },
                ],
            },
        };
        setDataOptionsPlayed(options);

        //------------ WIN ------------
        numb = [];
        labels = [];
        for(let i = 0 ; i < op.length ; i++){
            numb.push((op[i].WRate));
            labels.push(op[i].Name);
        }

        var data1 = {
            labels: labels,
            datasets: [
                {
                label: 'Winnig in %',
                data: numb,
                backgroundColor: 'rgba(102, 178, 255, 1)',
                borderColor: 'rgba(102, 178, 255, 1)',
                borderWidth: 1,
                },
            ],
        };
        setDataNumbersWin(data1);
         var options1 = {
            scales: {
                yAxes: [
                    {
                        ticks: {
                            beginAtZero: true,
                        },
                    },
                ],
            },
            
        };
        setDataOptionsWin(options1);
        
    },[]
    );
    return(  
        <>
        <div id = "GraphBar">
            <h3>Opening <br/>Preference</h3>
            <Bar data={dataNumbersPlayed} options={dataOptionsPlayed} id = "GraphBar"/>
        </div>
        <div id = "GraphBar">
            <h3>Best Result<br/>Opening</h3>
            <Bar data={dataNumbersWin} options={dataOptionsWin} id = "GraphBar"/>
        </div>
        </>
    );
};





export default ChartComponent;
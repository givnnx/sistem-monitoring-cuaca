let temperatureChart;
let humdityChart;

const addTemperatureChart = () => {
  let ctx = document.getElementById("temperatureChart").getContext("2d");

  if (!temperatureChart) {
    temperatureChart = new Chart(ctx, {
      type: "line",
      data: {
        labels: dataTempTime,
        datasets: [
          {
            label: "Temperature",
            data: dataTemp,
            fill: "start",
            borderColor: "rgba(255, 99, 132, 1)",
            backgroundColor: "rgba(255, 99, 132, 0.2)",
            tension: 0.4,
          },
          {
            label: "Humidity",
            data: dataHum,
            fill: "start",
            borderColor: "rgba(200, 99, 12, 1)",
            backgroundColor: "rgba(255, 99, 13, 0.2)",
            tension: 0.4,
          },
        ],
      },
      options: {
        responsive: true,
        scales: {
          y: {
            beginAtZero: true,
          },
        },
      },
    });
  }

  temperatureChart.update();
};

const addHumidityChart = () => {
  let ctx = document.getElementById("humidityChart").getContext("2d");

  if (!humdityChart) {
    humdityChart = new Chart(ctx, {
      type: "line",
      data: {
        labels: dataHumTime,
        datasets: [
          {
            label: "Humidity",
            data: dataHum,
            fill: "start",
            borderColor: "rgba(200, 99, 12, 1)",
            backgroundColor: "rgba(255, 99, 13, 0.2)",
            tension: 0.4,
          },
        ],
      },
      options: {
        responsive: true,
        scales: {
          y: {
            beginAtZero: true,
          },
        },
      },
    });
  }

  humdityChart.update();
};

window.onload = { addTemperatureChart, addHumidityChart };

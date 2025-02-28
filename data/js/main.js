let tempDataArray = [];
let humDataArray = [];
let dataTemp = [];
let dataTempTime = [];
let dataHum = [];
let dataHumTime = [];

function updateDataTemp(data) {
  const tempElement = document.getElementById("temp");
  tempElement.textContent = `${data} °C`;
  updateTemperatureChartData(data);
  addTemperatureChart();
}

function updateDataHum(data) {
  const humidityElement = document.getElementById("humidity");
  humidityElement.textContent = `${data} %`;
  updateHumidityChartData(data);
  addHumidityChart();
}

let tempData = (data) => {
  if (tempDataArray.length > 100) tempDataArray.shift();
  tempDataArray.push({ temperature: data, timestamp: Date.now() });
  return { temperature: data, timestamp: Date.now() };
};

let humData = (data) => {
  if (tempDataArray.length > 100) tempDataArray.shift();
  humDataArray.push({ humidity: data, timestamp: Date.now().toLocaleString });
  return { humidity: data, timestamp: Date.now() };
};

function updateTemperatureChartData(data) {
  if (dataTemp.length > 5) {
    dataTemp.shift();
    dataTempTime.shift();
  }

  dataTemp.push(tempData(data).temperature);
  dataTempTime.push(formatMillisToCurrentTime(tempData(data).timestamp));
}

function updateHumidityChartData(data) {
  if (dataHum.length > 5) {
    dataHum.shift();
    dataHumTime.shift();
  }

  dataHum.push(humData(data).humidity);
  dataHumTime.push(formatMillisToCurrentTime(humData(data).timestamp));
}

function formatMillisToCurrentTime(milliseconds) {
  const date = new Date(milliseconds);

  const hours = date.getHours();
  const minutes = date.getMinutes();

  const formattedTime = `${hours.toString().padStart(2, "0")}:${minutes
    .toString()
    .padStart(2, "0")}`;

  return formattedTime;
}

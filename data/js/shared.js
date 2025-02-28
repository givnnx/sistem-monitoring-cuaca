let websocket = null;
let reconnecting = false;

function connectWebSocket() {
  websocket = new WebSocket("ws://192.168.1.4:8080/ws");

  websocket.onopen = () => {
    console.log("Connected to WebSocket");
    reconnecting = false;
  };

  websocket.onclose = () => {
    console.log("Disconnected from WebSocket");
    if (!reconnecting) {
      setTimeout(connectWebSocket, 5000);
      reconnecting = true;
    }
  };

  websocket.onerror = (error) => {
    console.error("WebSocket error:", error);
    if (!reconnecting) {
      setTimeout(connectWebSocket, 5000);
      reconnecting = true;
    }
  };

  websocket.onmessage = (event) => {
    try {
      const data = JSON.parse(event.data);

      if (!data.temperature) updateDataTemp(0);

      if (data.temperature) {
        updateDataTemp(data.temperature);
      }

      if (!data.humidity) updateDataHum(0);

      if (data.humidity) {
        updateDataHum(data.humidity);
      }
    } catch (error) {
      console.error("Error parsing JSON:", error);
    }
  };
}

connectWebSocket();



const token = '7tgFPmN33WqxR2SE_j9i8qgOh6pKQpru';
const apiUrlCommon = `https://blynk.cloud/external/api/get?token=${token}&`;
var dataValue;
console.log("inside the js")

function loadPage() {
    for(let i= 0; i<= 8; i++) {
        fetchData(i);
    }
}

document.addEventListener('DOMContentLoaded', loadPage);

function fetchData(value) {
    console.log(value + " value of the value")
    let switchId = "v"+value;
    const url = apiUrlCommon + "v" + value
    fetch(url)
        .then(response => {
    // Check if the response is successful
    if (!response.ok) {
      throw new Error('Failed to fetch data');
    }
    // Parse the JSON response
    return response.json();
  })
  .then(data => {
    // Extract the value from the response
    const variableValue = data; // Assuming the response is the value itself
    console.log('Variable value:', variableValue);
    // dataValue = variableValue;
    // console.log(dataValue + " data value,..............................")

    console.log(switchId + " switchId of the switch")
    const toggleButton = document.getElementById(switchId);
    console.log(toggleButton + " toggleButton")

    toggleButton.checked = (variableValue === 1); // Check if value is 1

    // You can do whatever you need with the variable value here
  })
  .catch(error => {
    console.error('Error:', error);
  });
}

  function updateData(checkbox, switchId) {
    const updateUrl = "https://blynk.cloud/external/api/update?token=7tgFPmN33WqxR2SE_j9i8qgOh6pKQpru&";
    const urlCommon = updateUrl + switchId+ "="

    const toggleButton = document.getElementById(switchId);
    const isChecked = toggleButton.checked ? 1 : 0; // Convert checkbox state to 1 (checked) or 0 (unchecked)
    const url = urlCommon + isChecked;

    console.log(url + " url,.")

    fetch(url)
    .then(response => {
                     // Check if the response is successful
                     if (!response.ok) {
                        throw new Error('Failed to update data');
                    }
                    console.log('Checkbox state updated successfully');
    })
    .catch(error => {
        console.error('Error:', error);
    });
  }

  function updateAPI(checkbox, switchId) {
    document.getElementById(switchId).addEventListener('change', updateData(checkbox, switchId));
  }
  // Function to update temperature gauge
function updateTemperatureGauge(temperatureValue) {
  const gauge = document.querySelector('.gauge.temperature');
  const needle = gauge.querySelector('.needle.temperature');
  const label = gauge.querySelector('.label.temperature');
  
  const angle = (temperatureValue / 100) * 180 - 90; // Assuming temperature range is 0-100
  needle.style.transform = `translateX(-50%) rotate(${angle}deg)`;
  label.textContent = `${temperatureValue.toFixed(2)} °C`; // Display temperature with 2 decimal places
}

// Function to update humidity gauge
function updateHumidityGauge(humidityValue) {
  const gauge = document.querySelector('.gauge.humidity');
  const needle = gauge.querySelector('.needle.humidity');
  const label = gauge.querySelector('.label.humidity');
  
  const angle = (humidityValue / 100) * 180 - 90; // Assuming humidity range is 0-100
  needle.style.transform = `translateX(-50%) rotate(${angle}deg)`;
  label.textContent = `${humidityValue.toFixed(2)} %`; // Display humidity with 2 decimal places
}

// Function to fetch data from API and update gauges
function fetchDataAndUpdateGauges() {
  // Replace 'apiUrlTemperature' and 'apiUrlHumidity' with the actual API endpoints
  const apiUrlTemperature = 'your_temperature_api_endpoint';
  const apiUrlHumidity = 'your_humidity_api_endpoint';

  // Fetch temperature data
  fetch(apiUrlTemperature)
      .then(response => response.json())
      .then(data => {
          const temperatureValue = data.temperature; // Assuming API response has a 'temperature' field
          updateTemperatureGauge(temperatureValue);
      })
      .catch(error => console.error('Error fetching temperature data:', error));

  // Fetch humidity data
  fetch(apiUrlHumidity)
      .then(response => response.json())
      .then(data => {
          const humidityValue = data.humidity; // Assuming API response has a 'humidity' field
          updateHumidityGauge(humidityValue);
      })
      .catch(error => console.error('Error fetching humidity data:', error));
}

// Call the function initially and set interval to update gauges periodically
fetchDataAndUpdateGauges(); // Initial update
setInterval(fetchDataAndUpdateGauges, 5000); // Update every 5 seconds (adjust as needed)

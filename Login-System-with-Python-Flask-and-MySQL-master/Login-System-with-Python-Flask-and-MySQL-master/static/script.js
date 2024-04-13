

const token = '7tgFPmN33WqxR2SE_j9i8qgOh6pKQpru';
const apiUrlCommon = `https://blynk.cloud/external/api/get?token=${token}&`;
var dataValue;
console.log("inside the js")

let numbersOfSwitchArray = [1,2,3,5,8];
let numbersOfTempArray = [9,10];

function loadPage() {
  for (let number of numbersOfSwitchArray) {
      fetchData(number);
  }

  for (let number of numbersOfTempArray) {
    fetchTempData(number);
  }
}

function fetchTempData(value) {
  console.log(value + " value of the value")
  let switchId = "v"+value;
  const url = apiUrlCommon + "v" + value
  console.log(url + " url..............");
  fetch(url)
      .then(response => {
  // Check if the response is successful
  console.log(response + " response,.........")
  if (!response.ok) {
    throw new Error('Failed to fetch data');
  }
  // Parse the JSON response
  return response.json();
})
.then(data => {
  // Extract the value from the response
  const variableValue = data; // Assuming the response is the value itself
  console.log('Variable value: in temp', variableValue);

  if(value == 9) {
    updateTemperatureGauge(variableValue); // Update temperature gauge
  } else{
    updateHumidityGauge(variableValue);
  }
})
.catch(error => {
  console.error('Error:', error);
});
}

// Function to update temperature gauge
function updateTemperatureGauge(temperatureValue) {
  const temperatureLabel = document.getElementById('v9'); // Get temperature label element
  temperatureLabel.textContent = temperatureValue + ' °C'; // Update temperature value
  
  const gauge = document.querySelector('.gauge.temperature');
  const needle = gauge.querySelector('.needle.temperature');
  
  // Calculate the angle of rotation based on temperature value (assuming temperature range is 1-100)
  const angle = ((temperatureValue - 1) / 99) * 180 - 90;
  
  // Apply the rotation to the needle
  needle.style.transform = `translateX(-50%) rotate(${angle}deg)`;
}

// Function to update humidity gauge
function updateHumidityGauge(humidityValue) {
  const humidityLabel = document.getElementById('v10'); // Get humidity label element
  humidityLabel.textContent = humidityValue + ' %'; // Update humidity value
  
  const gauge = document.querySelector('.gauge.humidity');
  const needle = gauge.querySelector('.needle.humidity');
  
  // Calculate the angle of rotation based on humidity value (assuming humidity range is 1-50)
  const angle = ((humidityValue - 1) / 49) * 180 - 90;
  
  // Apply the rotation to the needle
  needle.style.transform = `translateX(-50%) rotate(${angle}deg)`;
}


function fetchData(value) {
    console.log(value + " value of the value")
    let switchId = "v"+value;
    const url = apiUrlCommon + "v" + value
    console.log(url + " url..............");
    fetch(url)
        .then(response => {
    // Check if the response is successful
    console.log(response + " response,.........")
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

    console.log(switchId + " switchId of the switch")
    const toggleButton = document.getElementById(switchId);
    console.log(toggleButton + " toggleButton")

    toggleButton.checked = (variableValue === 1); // Check if value is 1

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
// Add more time in seconds
// setInterval(loadPage, 1000);

// Call loadPage initially and set interval to update periodically
loadPage();
setInterval(loadPage, 1000);

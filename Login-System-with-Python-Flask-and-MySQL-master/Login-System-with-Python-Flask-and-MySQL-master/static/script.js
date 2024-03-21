

const token = '7tgFPmN33WqxR2SE_j9i8qgOh6pKQpru';
const apiUrlCommon = `https://blynk.cloud/external/api/get?token=${token}&`;
var dataValue;
console.log("inside the js")


function loadPage() {
    for(let i= 0; i<= 8; i++) {
        fetchData(i);
    }
}

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
// Add more time in seconds
setInterval(loadPage, 1000);
# Blynk api documents

*Required Blynk api specifications based on primary usage*

<details id=0>
<summary><h2>Credentials </h2></summary>

## BLYNK_AUTH_TOKEN 

```
7N5w7p9EKaRyohKFI-99TTzPZ40kxUdR
```
## Network

> SSID ::   Anaa
  
> Password ::  crazy@ar

</details> 
<details id=1>
<summary><h2>Update the Datastream value </h2></summary>

This endpoint allows you to update the value of the Datastream value via GET request.

*Syntax*

> https://{server_address}/external/api/update?token={token}&{pin}={value}

### API link to update data

```
https://blynk.cloud/external/api/get?token=7N5w7p9EKaRyohKFI-99TTzPZ40kxUdR&v0=1
```
</details>
<details id=2>
<summary><h2> Get Datastream value</h2></summary>


This endpoint allows you to get the stored value of the Datastream by pin type and pin.

*Syntax*

> https://{server_address}/external/api/get?token={token}&{pin}

### API link to get data

```
https://blynk.cloud/external/api/get?token=7N5w7p9EKaRyohKFI-99TTzPZ40kxUdR&v0
```
</details>

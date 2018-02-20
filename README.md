submit data

{
  "value": "27",
}

curl -F 'value=65.5' -H 'X-AIO-Key: 37e1300e78ff4d7baf01ef9a45febe21' \
  https://io.adafruit.com/api/v2/xylifyx/feeds/humitemp1/data

  curl -F "value=$(shuf -i 1-100 -n 1)" -H 'X-AIO-Key
: 37e1300e78ff4d7baf01ef9a45febe21'   https://io.adafruit.com/api/v2/xylifyx/feeds/humitemp1/data


 mosquitto_pub -h io.adafruit.com -m '{"value": '$(shuf -i 1-100 -n 1)'}' -u xylifyx -P 37e1300e78ff4d7baf01ef9a45febe21 -t xylifyx/feeds/humitemp1

 

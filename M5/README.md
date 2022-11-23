<h1> To run the Arduino code </h1>
<ol type="1">
  <li> Go to BLE_Streaming/ directory, open the file BLE_Streaming.ino with Arduino IDE </li>
  <li> Choose the right port and board, then upload the code </li>
</ol>

<h1> To run the Pong game </h1>
<ol type="1">
  <li> In the M4 directory, run <b>node central.js</b> </li>
  <li> Then go to 127.0.0.1:3000 to play the game </li>
</ol>

<h1> How to play </h1>
This the pong game paddle is controlled by the gyroscope of arduino board, specifically by the x-axis. I adjusted the transform function so that the harder palyer twists the board in x-axis, the faster the paddle will move.
The speed of paddle, or delta Y increases as the score goes higher.

<h1> Credit </h1>
I did not write the pong game, the credit of pong game part in javascript goes to <b>crossPHD</b>, codes are directly copied and pasted from <b> https://github.com/crossphd/pong-js </b>.

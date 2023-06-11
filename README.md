# Siv3D_WheelSimulator

## シミュレーションアプリケーションの使い方

![robot_simulation](https://user-images.githubusercontent.com/98096559/244943218-2194f28d-c7cb-4644-af9e-51b01e5e5c22.png)

_ロボットの表示形式_

- チェックマークを入れると、画面中央にロボットが固定されます。

- チェックマークをのけると、ロボットが入力に応じて移動するようになります。

![robot_state](https://user-images.githubusercontent.com/98096559/244943258-40a1bcc5-caf7-4d2b-b6de-5e588bc10270.png)

_ロボットスピード_

- ロボットの各タイヤの最大ベクトルの速度を設定します。
- 0 から 255 までの数値を設定できることができます。
- オムニホイールと独立ステアリング制御での最大速度の差を実感することができると思います。

![robot_speed](https://user-images.githubusercontent.com/98096559/244943242-f7045d8c-4dff-4e4c-a6e7-73f687f835bf.png)

_入力モード_

- キーボード入力モード

  - W,A,S,D によって、前後左右の移動を行い、右矢印、左矢印により、旋回の入力をすることができます。

- PS5 コントローラ入力モード
  - コントローラの左スティックの入力により、前後左右の入力を行い、右スティックの入力によって旋回を行います。

![robot_input](https://user-images.githubusercontent.com/98096559/244943274-42a13572-2e57-4366-bae6-7a96dc56e91f.png)

_ロボットの計算モード_

- Omni-Mode

  - 4 輪オムニホイールのベクトル計算を行います。

- Steering-Mode

  - 独立 4 輪ステアリング機構のベクトル計算を行います。

![robot_output](https://user-images.githubusercontent.com/98096559/244943287-aadaf3e5-774c-4b02-a26d-1ecdeb68490f.png)

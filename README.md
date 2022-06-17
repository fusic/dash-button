# Fusicダッシュボタン

## 使用する準備

### クラウド

クラウド側のアプリケーションはAWS Lambdaで動作するプログラムです。AWS SAM CLIを用いて以下のようにビルド・デプロイします。

```sh
$ sam build
$ sam deploy --guided
```

SORACOM Funkの認証用のIAM Roleを作成してください。

- [SORACOM Funk - 証情報ストアに AWS IAM ロール認証情報を登録する](https://users.soracom.io/ja-jp/docs/funk/aws-lambda/#%e8%aa%8d%e8%a8%bc%e6%83%85%e5%a0%b1%e3%82%b9%e3%83%88%e3%82%a2%e3%81%ab-aws-iam-%e3%83%ad%e3%83%bc%e3%83%ab%e8%aa%8d%e8%a8%bc%e6%83%85%e5%a0%b1%e3%82%92%e7%99%bb%e9%8c%b2%e3%81%99%e3%82%8b)

### 通信

SORACOM Arcの仮想SIMを作成してください。

- [SORACOM Arc - バーチャル SIM/Subscriber を作成する](https://users.soracom.io/ja-jp/docs/arc/create-virtual-sim/)

デプロイしたLambdaを実行するようSORACOM Funkを有効化してください。

- [SORACOM Funk - SORACOM Funkを有効化する](https://users.soracom.io/ja-jp/docs/funk/enable-funk/)

### デバイス

1. デバイス(M5Stack)をPCに接続します
2. Arduino IDEで `device` ディレクトリ配下の `main.ino` を開きます
3. Arduino IDEでプログラムをUploadします
4. お手持ちのスマートフォンでM5StackのLCDに表示されたアクセスポイント `ESP32_XXXXXXXX` へ接続します
5. Wi-FiのSSID, PasswordおよびSORACOM Arcで作成した仮想SIMの情報を入力します

## 使い方

1. デバイス(M5Stack)を電源に接続します
2. メニューが表示されたらM5StackのA, Cボタンでカーソルを上下させ、消耗品を選択します
3. 通知したい消耗品の横にカーソルが来たら、Bボタンで通知します
4. Slackの指定したチャンネルに、消耗品の減少が通知されます

## ライセンス

MIT LICENSE

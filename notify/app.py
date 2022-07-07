# import json
import os
from slack_sdk import WebClient
from slack_sdk.errors import SlackApiError

def lambda_handler(event, context):
    client = WebClient(token=os.environ['SLACK_BOT_TOKEN'])
    channel = os.environ['SLACK_CHANNEL']
    items = [
        { 'name': 'インスタントコーヒー', 'url': 'https://www.askul.co.jp/p/9926956/' },
        { 'name': 'マドラー', 'url': 'https://www.askul.co.jp/p/9651667/' },
        { 'name': '紙コップ', 'url': 'https://www.askul.co.jp/p/8467349/' },
        { 'name': '箱ティッシュ', 'url': 'https://www.askul.co.jp/p/1618138/' },
        { 'name': 'ウェットティッシュ', 'url': 'https://www.askul.co.jp/p/1186355/' },
        { 'name': 'ペーパータオル', 'url': 'https://www.askul.co.jp/p/1995269/' },
        { 'name': '来客用水', 'url': 'https://www.askul.co.jp/p/AR51978/' },
    ]
    print(event)
    try:
        item = items[event['item']]
        message = f"<!subteam^{os.environ['SLACK_MENSION_ID']}> {item['name']}の在庫が少なくなりました\n{item['url']}"
        response = client.chat_postMessage(channel=channel, text=message)
        assert response["message"]["text"] == message
    except SlackApiError as e:
        assert e.response["ok"] is False
        assert e.response["error"]
        print(f"Got an error: {e.response['error']}")

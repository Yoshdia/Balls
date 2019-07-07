#pragma once

/*          コーディングルール          
・Tabは禁止                     
・using namespace,usingは禁止
・インクルード順はgoogleに準じる
1.自身のソース対するヘッダ
2.Cシステムファイル
3.C++システムファイル
4.その他ライブラリの.h ファイル(boost / opencv など)
5.プロジェクトの.h ファイル
・命名規則
camelCase
 メソッド名や変数名
PascalCase
 const変数や関数名、クラス名など
アンダースコアを使用した命名は禁止

・ブーリアンとの比較は禁止
・トークン
TODO	未実装	要件を満たすために追加実装が必須な状態。
コミット・PR・タスク等の区切りなどで利用。
FIXME	修正が必要	要件を満たすために修正が必須な状態。
モック実装等、暫定的に動作させるケースなどで利用。
OPTIMIZE	性能改善を推奨	要件は満たしているが、性能が不安視される状態。
後から性能の計測や改善したいケースなどで利用。
HACK	設計や記述の改善を推奨	要件は満たしているが、保守性や可読性に乏しい状態。
後から整理したいケースなどで利用。
NOTE	コメント確認を推奨	通常コメントより目立たせることが主目的であり、使途は自由。
不可解な実装の経緯や背景などで利用


・破ると加点される壁を実装
　(後だし負けジャンケンのような)
・壁を破れるようになるアイテム
　(スター、パックマンの逆転アイテム)

・一定距離ごとにステージ変更演出
　(跳躍など)
→さらにカメラの方向を変え飽きさせないなど
・単純な四角形を大量に出現、回転させて立体的なトンネルを連想させる*/





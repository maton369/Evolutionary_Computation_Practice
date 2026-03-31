#include "FlowerSet.h"

/*
    ============================================================
    main.cpp
    ============================================================

    このファイルは、人工蜂コロニーアルゴリズム全体の実行フローを記述する。

    main 自体は短いが、その短さは責務分離がうまくできている証拠でもある。

    実際の役割分担は次の通りである。

    - Dataset
      問題データと回帰式解釈を担当

    - Flower
      1つの候補解（食糧源）を担当

    - FlowerSet
      ABC の3フェーズと最良解管理を担当

    - main
      外側の反復制御だけを担当

    つまり main は、
    「アルゴリズム全体の枠組みだけを記述し、
     詳細処理は各クラスへ委譲している」
    という設計になっている。
*/

int main()
{
    int i;
    FlowerSet* fSet;

    /*
        疑似乱数の seed を現在時刻で初期化する。

        ABC は確率的最適化アルゴリズムであり、
        初期食糧源の配置や近傍探索に乱数を用いる。

        したがって seed によって探索過程が変わる。
        実験再現のためには固定 seed を使うことも多い。
    */
    srand((unsigned int)time(NULL));

    /*
        FlowerSet を生成する。

        ここで通常は、
        - Dataset の読み込み
        - 初期食糧源の生成
        - 最良解用領域の初期化
        が行われる想定である。
    */
    fSet = new FlowerSet((char*)"sampledata.csv");

    /*
        ABC の反復ループ。

        1回の反復で行う処理は、

            1. employedBeePhase()
            2. onlookerBeePhase()
            3. scoutBeePhase()
            4. saveBestPos()

        である。

        これは ABC の標準的な 1 サイクルに対応している。

        --------------------------------------------------------
        1. employed bee
           各食糧源の局所改良
        2. onlooker bee
           良い食糧源への探索集中
        3. scout bee
           停滞食糧源の再初期化
        4. best 保存
           これまでの最良解を追跡
        --------------------------------------------------------

        つまりこのループ全体は、
        exploit と explore を交互に進めながら
        最良解を更新していく過程を表している。
    */
    for (i = 1; i <= REPEAT_NUM; i++) {
        fSet->employedBeePhase();
        fSet->onlookerBeePhase();
        fSet->scoutBeePhase();
        fSet->saveBestPos();

        /*
            各反復で現在の最良評価値を表示する。

            これにより、
            探索が順調に進んでいるか、
            途中で停滞していないか、
            を簡易的に観察できる。
        */
        printf("%d回目：最良評価値%f\n", i, fSet->bestValue);
    }

    /*
        最終結果を表示する。

        実験用途では、
        - 最良係数ベクトル
        - 最良評価値
        - 回帰式
        などがここで出力されることが期待される。
    */
    fSet->printResult();

    /*
        後始末。

        FlowerSet が所有する Dataset や Flower 群も
        ここで連鎖的に解放される想定である。
    */
    delete fSet;

    return 0;
}

#ifndef DATASET_H
#define DATASET_H

/*
    ============================================================
    Dataset.h
    ============================================================

    このファイルでは、ABC が最適化対象とするデータセットを表す Dataset クラスを定義する。

    ------------------------------------------------------------
    Dataset の役割
    ------------------------------------------------------------

    このクラスは単なる入力データ保存だけでなく、

    - 説明変数と目的変数のデータ保持
    - 標準化データの保持
    - 回帰係数への変換
    - 最終的な回帰式表示

    を担当している。

    したがって Dataset は、
    「ABC が探索する候補解をどう解釈するか」
    を定める問題定義クラスである。

    Flower が「候補解ベクトル」を持っていても、
    それが実際にどんな意味を持つかは Dataset を通じて初めて決まる。
*/

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

class Dataset {
public:
    /*
        コンストラクタ。

        fileName からデータを読み込み、
        説明変数・目的変数・標準化データ・平均・標準偏差などを初期化する想定である。
    */
    Dataset(char* fileName);

    /*
        デストラクタ。

        各動的配列の解放責任を持つ。
    */
    ~Dataset();

    /*
        setCoef(sCoef):
            標準偏回帰係数 sCoef から偏回帰係数 coef を求める。

            Flower の pos が標準化空間での係数なら、
            実際の元データスケールでの回帰式へ戻すには変換が必要になる。

            この関数はその橋渡しを行う。
    */
    void setCoef(double* sCoef);

    /*
        printEquation():
            最終的な重回帰式を表示する。

            最適化後の bestPos を人間が解釈可能な回帰式へ変換して示す用途が想定される。
    */
    void printEquation();

    /*
        dataNum:
            データ数（サンプル数）。
    */
    int dataNum;

    /*
        exVarNum:
            説明変数の個数。

            Flower の pos ベクトル次元は通常これに一致する。
    */
    int exVarNum;

    /*
        exData:
            説明変数データ（元スケール）。
    */
    double** exData;

    /*
        resData:
            目的変数データ（元スケール）。
    */
    double* resData;

    /*
        exSData:
            説明変数データ（標準化済み）。

            ABC の探索を標準化空間で安定に行うために使われると考えられる。
    */
    double** exSData;

    /*
        resSData:
            目的変数データ（標準化済み）。
    */
    double* resSData;

    /*
        coef:
            偏回帰係数。

            標準偏回帰係数から実スケールへ戻した後の係数を保持する。
    */
    double* coef;

    /*
        constant:
            回帰式の定数項。
    */
    double constant;

private:
    /*
        exAve:
            各説明変数の平均。
    */
    double* exAve;

    /*
        resAve:
            目的変数の平均。
    */
    double resAve;

    /*
        exSd:
            各説明変数の標準偏差。
    */
    double* exSd;

    /*
        resSd:
            目的変数の標準偏差。
    */
    double resSd;
};

#endif

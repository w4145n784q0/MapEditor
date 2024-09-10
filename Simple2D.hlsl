//	//───────────────────────────────────────
//// テクスチャ＆サンプラーデータのグローバル変数定義
////───────────────────────────────────────
    Texture2D g_texture : register(t0); //テクスチャー
    SamplerState g_sampler : register(s0); //サンプラー
//}
//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
    //変換行列、視点、光源
    float4x4 matW;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
    float4 pos : SV_POSITION; //位置
    float2 uv : TEXCOORD; //UV座標
};
//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD)
{
	//ピクセルシェーダーへ渡す情報
    VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
    //スクリーン座標に変換し、 ピクセルシェーダーへ

    outData.pos = mul(pos, matW);
    outData.uv = uv;
    
    //float4 light = float4(1, 0.8, 0.3, 0); //光源ベクトルの逆ベクトル
    //light = normalize(light); //単位ベクトル化
    //normal = mul(normal, matW);
    //normal = normalize(normal);
    //outData.cos_alpha = clamp(dot(normal, light), 0, 1);
    
    //まとめて出力

    return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    return g_texture.Sample(g_sampler, inData.uv);
   // return float4(65/255, 105/255, 225/255, 1);
    //float4 my = { 0.125, 0.25, 0, 0 };
    //float4 Id = { 1.0, 1.0, 1.0, 1.0 };
    //float4 Kd = g_texture.Sample(g_sampler, inData.uv);
    //float cos_alpha = inData.cos_alpha;
    //float4 ambentSource = { 0.2, 0.2, 0.2, 1.0 }; //環境光の強さ
   
    //return Id * Kd * cos_alpha + Id * Kd * ambentSource;
    
    
    
    //return g_texture.Sample(g_sampler, inData.uv);
    //return g_texture.Sample(g_sampler, my);
}


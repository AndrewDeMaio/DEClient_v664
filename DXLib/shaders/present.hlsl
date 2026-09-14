// present.hlsl - pixel shaders for the GPU present layer (CD3D9Scaler).
//
// Both shaders are ps_2_0 so they run on any D3D9-class GPU and work with
// the fixed-function pretransformed quad the presenter already draws.
// Rebuild the headers with build_shaders.bat after editing.
//
// Constants (set by CD3D9Scaler):
//   c0 = (texW, texH, 1/texW, 1/texH)      size of the texture being sampled
//   c1 = (texelsPerPixelX, texelsPerPixelY, sharpness 0..1, unused)

sampler2D s0 : register(s0);
float4    c0 : register(c0);
float4    c1 : register(c1);

// Sharp bilinear ("pixel AA"): each texel is shown as a solid block with a
// one-screen-pixel-wide blend at its edges, whatever the scale ratio. Avoids
// the softness of plain bilinear and the shimmer of nearest at 1.5x. When
// the ratio is >= 1 texel per pixel (downscaling) it degrades to bilinear.
float4 PS_Sharp(float2 uv : TEXCOORD0) : COLOR
{
    float2 pix = uv * c0.xy - 0.5;          // texel space, 0 = centre of texel 0
    float2 i   = floor(pix);
    float2 f   = pix - i;                   // 0 at centre of texel i, 1 at centre of i+1
    float2 w   = min(c1.xy, 1.0);           // blend width in texels = one screen pixel
    float2 t   = saturate((f - 0.5) / w + 0.5);
    float2 uv2 = (i + 0.5 + t) * c0.zw;     // hardware bilinear does the blend
    return tex2D(s0, uv2);
}

// Contrast-adaptive sharpening (AMD CAS, single pass, cross taps). Runs 1:1
// on the already-scaled frame. c1.z = strength 0..1.
float4 PS_Cas(float2 uv : TEXCOORD0) : COLOR
{
    float2 px = c0.zw;
    float3 n = tex2D(s0, uv + float2(0.0, -px.y)).rgb;
    float3 w = tex2D(s0, uv + float2(-px.x, 0.0)).rgb;
    float3 c = tex2D(s0, uv).rgb;
    float3 e = tex2D(s0, uv + float2(px.x, 0.0)).rgb;
    float3 s = tex2D(s0, uv + float2(0.0, px.y)).rgb;

    float3 mn = min(min(min(n, w), min(c, e)), s);
    float3 mx = max(max(max(n, w), max(c, e)), s);
    float3 rcpM = 1.0 / max(mx, 0.0001);
    float3 amp  = sqrt(saturate(min(mn, 2.0 - mx) * rcpM));
    float  peak = -1.0 / (8.0 - 3.0 * saturate(c1.z));   // -1/8 .. -1/5
    float3 wgt  = amp * peak;
    float3 col  = (wgt * (n + w + e + s) + c) / (4.0 * wgt + 1.0);
    return float4(saturate(col), 1.0);
}

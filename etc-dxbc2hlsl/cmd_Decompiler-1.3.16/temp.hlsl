// ---- Created with 3Dmigoto v1.3.16 on Thu May 30 16:39:44 2024
Texture2D<float4> t7 : register(t7);

Texture2D<float4> t6 : register(t6);

Texture2D<float4> t5 : register(t5);

TextureCube<float4> t4 : register(t4);

Texture2D<float4> t3 : register(t3);

Texture2D<float4> t2 : register(t2);

Texture2D<float4> t1 : register(t1);

Texture2D<float4> t0 : register(t0);

SamplerState s5_s : register(s5);

SamplerState s4_s : register(s4);

SamplerState s3_s : register(s3);

SamplerState s2_s : register(s2);

SamplerState s1_s : register(s1);

SamplerState s0_s : register(s0);

cbuffer cb3 : register(b3)
{
  float4 cb3[18];
}

cbuffer cb2 : register(b2)
{
  float4 cb2[14];
}

cbuffer cb1 : register(b1)
{
  float4 cb1[180];
}

cbuffer cb0 : register(b0)
{
  float4 cb0[44];
}




// 3Dmigoto declarations
#define cmp -


void main(
  float4 v0 : TEXCOORD10,
  float4 v1 : TEXCOORD11,
  float4 v2 : COLOR0,
  float4 v3 : TEXCOORD0,
  float2 v4 : TEXCOORD1,
  float4 v5 : COLOR1,
  float4 v6 : TEXCOORD7,
  float4 v7 : TEXCOORD8,
  float4 v8 : SV_Position0,
  uint v9 : SV_IsFrontFace0,
  out float4 o0 : SV_Target0)
{
  float4 r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18;
  uint4 bitmask, uiDest;
  float4 fDest;

  r0.xyz = v1.yzx * v0.xyz;
  r0.xyz = v1.xyz * v0.yzx + -r0.xyz;
  r0.xyz = v1.www * r0.xyz;
  r1.xy = -cb1[159].xy + v8.xy;
  r1.xy = r1.xy * cb1[115].zw + float2(-0.5,-0.5);
  r1.xy = v8.ww * r1.xy;
  r1.z = v8.w;
  r0.w = dot(-v7.xyz, -v7.xyz);
  r0.w = rsqrt(r0.w);
  r2.xyz = -v7.xyz * r0.www;
  r3.xy = t1.Sample(s1_s, v3.xy).xy;
  r3.xy = r3.xy * float2(2,2) + float2(-1,-1);
  r1.w = dot(r3.xy, r3.xy);
  r1.w = 1 + -r1.w;
  r1.w = max(0, r1.w);
  r1.w = sqrt(r1.w);
  r3.z = 1 + r1.w;
  r4.xyz = t2.Sample(s2_s, v4.xy).xyz;
  r5.xy = r4.xy * float2(2,2) + float2(-1,-1);
  r1.w = -r5.x * r5.x + 1;
  r1.w = -r5.y * r5.y + r1.w;
  r1.w = max(0, r1.w);
  r5.z = sqrt(r1.w);
  r4.xyw = float3(0,0,1) + -r5.xyz;
  r4.xyw = cb3[17].yyy * r4.xyw + r5.xyz;
  r4.xyw = float3(-1,-1,1) * r4.xyw;
  r1.w = dot(r3.xyz, r4.xyw);
  r4.xyw = r4.xyw * r3.zzz;
  r3.xyz = r3.xyz * r1.www + -r4.xyw;
  r3.xyz = r3.xyz * cb1[162].www + cb1[162].xyz;
  r0.xyz = r3.yyy * r0.xyz;
  r0.xyz = r3.xxx * v0.zxy + r0.xyz;
  r0.xyz = r3.zzz * v1.zxy + r0.xyz;
  r1.w = dot(r0.xyz, r0.xyz);
  r1.w = rsqrt(r1.w);
  r0.xyz = r1.www * r0.xyz;
  r1.w = dot(r0.yzx, r2.xyz);
  r3.xyz = r1.www * r0.yzx;
  r3.xyz = r3.xyz * float3(2,2,2) + -r2.xyz;
  r4.xyw = t3.Sample(s3_s, v3.xy).xyz;
  r4.xyw = cb3[5].xyz * r4.xyw;
  r4.xyz = r4.xyw * r4.zzz;
  r2.w = 1 + -cb3[17].w;
  r2.w = 1 + -r2.w;
  r5.xyz = max(float3(0,0,0), cb3[2].xyz);
  r3.w = saturate(cb3[17].z);
  r4.w = r2.w * cb1[163].y + cb1[163].x;
  r4.xyzw = max(float4(0,0,0,0.119999997), r4.xyzw);
  r4.w = min(1, r4.w);
  r1.w = max(0, r1.w);
  r5.w = saturate(cb1[179].y);
  r6.x = max(0, cb0[36].x);
  r5.w = r6.x * r5.w;
  r6.x = cb0[36].z + r3.w;
  r6.x = min(1, r6.x);
  r6.x = r6.x + -r3.w;
  r3.w = r5.w * r6.x + r3.w;
  r6.x = r4.w * cb0[36].w + -r4.w;
  r4.w = r5.w * r6.x + r4.w;
  r6.x = dot(v1.xyz, v1.xyz);
  r6.x = rsqrt(r6.x);
  r5.w = 0.699999988 * r5.w;
  r6.xyz = v1.zxy * r6.xxx + -r0.xyz;
  r0.xyz = r5.www * r6.xyz + r0.xyz;
  r6.xyz = -r4.xyz * r3.www + r4.xyz;
  r5.w = -r3.w * 0.0399999991 + 0.0399999991;
  r7.xyz = r4.xyz * r3.www + r5.www;
  r8.xyzw = r4.wwww * float4(-1,-0.0274999999,-0.572000027,0.0219999999) + float4(1,0.0425000004,1.03999996,-0.0399999991);
  r3.w = r8.x * r8.x;
  r1.xyzw = float4(2,-2,1,-9.27999973) * r1.xyzw;
  r1.w = exp2(r1.w);
  r1.w = min(r3.w, r1.w);
  r1.w = r1.w * r8.x + r8.y;
  r8.xy = r1.ww * float2(-1.03999996,1.03999996) + r8.zw;
  r1.w = saturate(50 * r7.y);
  r1.w = r8.y * r1.w;
  r7.xyz = r7.xyz * r8.xxx + r1.www;
  r6.xyz = r6.xyz * cb1[160].www + cb1[160].xyz;
  r7.xyz = r7.xyz * cb1[161].www + cb1[161].xyz;
  r8.xyz = v5.xyz * r6.xyz;
  r1.w = dot(cb1[170].xyz, float3(0.300000012,0.589999974,0.109999999));
  r1.w = v5.w * r1.w;
  r8.xyz = cb1[170].xyz * r8.xyz;
  r8.xyz = cb1[179].zzz * r8.xyz;
  r3.w = cmp(r1.z < cb2[8].x);
  r9.xyz = cb2[11].xyz * r1.yyy;
  r9.xyz = r1.xxx * cb2[10].xyz + r9.xyz;
  r1.xyz = r1.zzz * cb2[12].xyz + r9.xyz;
  r1.xyz = cb2[13].xyz + r1.xyz;
  r1.xyz = r3.www ? r1.xyz : 0;
  r3.w = cmp(0 < r1.z);
  if (r3.w != 0) {
    r1.z = min(0.999989986, r1.z);
    r9.xyzw = cb2[6].xyxy * r1.xyxy;
    r10.xy = frac(r9.zw);
    r9.xyzw = floor(r9.xyzw);
    r11.xyzw = float4(-3,-3,-2,-3) + r9.zwzw;
    r11.xyzw = cb2[6].zwzw * r11.xyzw;
    r12.x = t0.SampleLevel(s0_s, r11.xy, 0).x;
    r12.y = t0.SampleLevel(s0_s, r11.zw, 0).x;
    r11.xyzw = float4(-1,-3,0,-3) + r9.zwzw;
    r11.xyzw = cb2[6].zwzw * r11.xyzw;
    r12.z = t0.SampleLevel(s0_s, r11.xy, 0).x;
    r12.w = t0.SampleLevel(s0_s, r11.zw, 0).x;
    r11.xyzw = r12.xyzw + -r1.zzzz;
    r11.xyzw = saturate(r11.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r12.xyzw = float4(-3,-2,-2,-2) + r9.zwzw;
    r12.xyzw = cb2[6].zwzw * r12.xyzw;
    r13.x = t0.SampleLevel(s0_s, r12.xy, 0).x;
    r13.y = t0.SampleLevel(s0_s, r12.zw, 0).x;
    r12.xyzw = float4(-1,-2,0,-2) + r9.zwzw;
    r12.xyzw = cb2[6].zwzw * r12.xyzw;
    r13.z = t0.SampleLevel(s0_s, r12.xy, 0).x;
    r13.w = t0.SampleLevel(s0_s, r12.zw, 0).x;
    r12.xyzw = r13.xyzw + -r1.zzzz;
    r12.xyzw = saturate(r12.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r13.xyzw = float4(-3,-1,-2,-1) + r9.zwzw;
    r13.xyzw = cb2[6].zwzw * r13.xyzw;
    r14.x = t0.SampleLevel(s0_s, r13.xy, 0).x;
    r14.y = t0.SampleLevel(s0_s, r13.zw, 0).x;
    r13.xyzw = float4(-1,-1,0,-1) + r9.zwzw;
    r13.xyzw = cb2[6].zwzw * r13.xyzw;
    r14.z = t0.SampleLevel(s0_s, r13.xy, 0).x;
    r14.w = t0.SampleLevel(s0_s, r13.zw, 0).x;
    r13.xyzw = r14.xyzw + -r1.zzzz;
    r13.xyzw = saturate(r13.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r14.xyzw = float4(-3,0,-2,0) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r15.x = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r15.y = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(-1,0,1,-3) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r15.z = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r1.xy = cb2[6].zw * r9.zw;
    r15.w = t0.SampleLevel(s0_s, r1.xy, 0).x;
    r15.xyzw = r15.xyzw + -r1.zzzz;
    r15.xyzw = saturate(r15.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r1.x = 1 + -r10.x;
    r1.y = r11.x * r1.x + r11.y;
    r3.w = r12.x * r1.x + r12.y;
    r5.w = r13.x * r1.x + r13.y;
    r6.w = r15.x * r1.x + r15.y;
    r1.y = r1.y + r11.z;
    r3.w = r3.w + r12.z;
    r5.w = r5.w + r13.z;
    r6.w = r6.w + r15.z;
    r16.y = r11.w * r10.x + r1.y;
    r16.z = r12.w * r10.x + r3.w;
    r16.w = r13.w * r10.x + r5.w;
    r16.x = r15.w * r10.x + r6.w;
    r10.z = 1 + -r10.y;
    r10.w = 1;
    r1.y = dot(r16.xywz, r10.yzww);
    r1.y = 0.111111112 * r1.y;
    r17.x = min(1, r1.y);
    r11.x = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(2,-3,3,-3) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r11.y = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r11.z = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r11.xyz = r11.xyz + -r1.zzz;
    r11.xyz = saturate(r11.xyz * cb2[2].www + float3(1,1,1));
    r14.xyzw = float4(1,-2,2,-2) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r12.x = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r12.y = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(3,-2,1,-1) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r12.z = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r12.xyz = r12.xyz + -r1.zzz;
    r12.xyz = saturate(r12.xyz * cb2[2].www + float3(1,1,1));
    r13.x = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(2,-1,3,-1) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r13.y = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r13.z = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r13.xyz = r13.xyz + -r1.zzz;
    r13.xyz = saturate(r13.xyz * cb2[2].www + float3(1,1,1));
    r14.xyzw = float4(1,0,2,0) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r15.x = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r15.y = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(3,0,-3,1) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r15.z = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r15.xyz = r15.xyz + -r1.zzz;
    r15.xyz = saturate(r15.xyz * cb2[2].www + float3(1,1,1));
    r1.y = r11.w * r1.x + r11.x;
    r3.w = r12.w * r1.x + r12.x;
    r5.w = r13.w * r1.x + r13.x;
    r6.w = r15.w * r1.x + r15.x;
    r1.y = r1.y + r11.y;
    r3.w = r3.w + r12.y;
    r5.w = r5.w + r13.y;
    r6.w = r6.w + r15.y;
    r11.y = r11.z * r10.x + r1.y;
    r11.z = r12.z * r10.x + r3.w;
    r11.w = r13.z * r10.x + r5.w;
    r11.x = r15.z * r10.x + r6.w;
    r12.xyzw = r10.ywwy * float4(-1,1,1,1) + float4(1,0,0,0);
    r1.y = dot(r11.yzwx, r12.xyzw);
    r1.y = 0.111111112 * r1.y;
    r17.y = min(1, r1.y);
    r13.x = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(-2,1,-1,1) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r13.y = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r13.z = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r14.xyzw = float4(0,1,-3,2) + r9.zwzw;
    r14.xyzw = cb2[6].zwzw * r14.xyzw;
    r13.w = t0.SampleLevel(s0_s, r14.xy, 0).x;
    r13.xyzw = r13.xyzw + -r1.zzzz;
    r13.xyzw = saturate(r13.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r14.x = t0.SampleLevel(s0_s, r14.zw, 0).x;
    r15.xyzw = float4(-2,2,-1,2) + r9.zwzw;
    r15.xyzw = cb2[6].zwzw * r15.xyzw;
    r14.y = t0.SampleLevel(s0_s, r15.xy, 0).x;
    r14.z = t0.SampleLevel(s0_s, r15.zw, 0).x;
    r15.xyzw = float4(0,2,-3,3) + r9.zwzw;
    r15.xyzw = cb2[6].zwzw * r15.xyzw;
    r14.w = t0.SampleLevel(s0_s, r15.xy, 0).x;
    r14.xyzw = r14.xyzw + -r1.zzzz;
    r14.xyzw = saturate(r14.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r15.x = t0.SampleLevel(s0_s, r15.zw, 0).x;
    r18.xyzw = float4(-2,3,-1,3) + r9.zwzw;
    r18.xyzw = cb2[6].zwzw * r18.xyzw;
    r15.y = t0.SampleLevel(s0_s, r18.xy, 0).x;
    r15.z = t0.SampleLevel(s0_s, r18.zw, 0).x;
    r18.xyzw = float4(0,3,1,1) + r9.zwzw;
    r18.xyzw = cb2[6].zwzw * r18.xyzw;
    r15.w = t0.SampleLevel(s0_s, r18.xy, 0).x;
    r15.xyzw = r15.xyzw + -r1.zzzz;
    r15.xyzw = saturate(r15.xyzw * cb2[2].wwww + float4(1,1,1,1));
    r1.y = r13.x * r1.x + r13.y;
    r3.w = r14.x * r1.x + r14.y;
    r5.w = r15.x * r1.x + r15.y;
    r1.y = r1.y + r13.z;
    r3.w = r3.w + r14.z;
    r5.w = r5.w + r15.z;
    r16.y = r13.w * r10.x + r1.y;
    r16.z = r14.w * r10.x + r3.w;
    r16.w = r15.w * r10.x + r5.w;
    r1.y = dot(r16.xyzw, r12.xyzw);
    r1.y = 0.111111112 * r1.y;
    r17.z = min(1, r1.y);
    r10.y = t0.SampleLevel(s0_s, r18.zw, 0).x;
    r16.xyzw = float4(2,1,3,1) + r9.zwzw;
    r16.xyzw = cb2[6].zwzw * r16.xyzw;
    r10.z = t0.SampleLevel(s0_s, r16.xy, 0).x;
    r10.w = t0.SampleLevel(s0_s, r16.zw, 0).x;
    r10.yzw = r10.yzw + -r1.zzz;
    r10.yzw = saturate(r10.yzw * cb2[2].www + float3(1,1,1));
    r16.xyzw = float4(1,2,2,2) + r9.zwzw;
    r16.xyzw = cb2[6].zwzw * r16.xyzw;
    r13.x = t0.SampleLevel(s0_s, r16.xy, 0).x;
    r13.y = t0.SampleLevel(s0_s, r16.zw, 0).x;
    r16.xyzw = float4(3,2,1,3) + r9.zwzw;
    r16.xyzw = cb2[6].zwzw * r16.xyzw;
    r13.z = t0.SampleLevel(s0_s, r16.xy, 0).x;
    r13.xyz = r13.xyz + -r1.zzz;
    r13.xyz = saturate(r13.xyz * cb2[2].www + float3(1,1,1));
    r14.x = t0.SampleLevel(s0_s, r16.zw, 0).x;
    r9.xyzw = float4(2,3,3,3) + r9.xyzw;
    r9.xyzw = cb2[6].zwzw * r9.xyzw;
    r14.y = t0.SampleLevel(s0_s, r9.xy, 0).x;
    r14.z = t0.SampleLevel(s0_s, r9.zw, 0).x;
    r9.xyz = r14.xyz + -r1.zzz;
    r9.xyz = saturate(r9.xyz * cb2[2].www + float3(1,1,1));
    r1.y = r13.w * r1.x + r10.y;
    r1.z = r14.w * r1.x + r13.x;
    r1.x = r15.w * r1.x + r9.x;
    r1.y = r1.y + r10.z;
    r1.z = r1.z + r13.y;
    r1.x = r1.x + r9.y;
    r11.y = r10.w * r10.x + r1.y;
    r11.z = r13.z * r10.x + r1.z;
    r11.w = r9.z * r10.x + r1.x;
    r1.x = dot(r11.xyzw, r12.xyzw);
    r1.x = 0.111111112 * r1.x;
    r17.w = min(1, r1.x);
    r1.x = dot(r17.xyzw, float4(0.25,0.25,0.25,0.25));
  } else {
    r1.x = 1;
  }
  r9.xyz = float3(1,1,1) + -cb0[34].xyz;
  r9.xyz = r1.xxx * r9.xyz + cb0[34].xyz;
  r8.xyz = r9.xyz * r8.xyz;
  r1.yz = cb1[116].zw * v8.xy;
  r3.w = t6.Sample(s5_s, r1.yz).x;
  r3.w = -1 + r3.w;
  r3.w = cb0[39].x * r3.w + 1;
  r9.xyz = t7.Sample(s5_s, r1.yz).xyz;
  r9.xyz = cb0[43].xxx * r9.xyz;
  r9.xyz = r9.xyz * r6.xyz;
  r8.xyz = r8.xyz * r3.www + r9.xyz;
  r3.w = dot(r0.yzx, cb2[3].xyz);
  r9.xyz = -v7.yzx * r0.www + cb2[3].yzx;
  r0.w = dot(r9.xyz, r9.xyz);
  r0.w = rsqrt(r0.w);
  r9.xyz = r9.xyz * r0.www;
  r0.w = dot(r0.zxy, r9.xyz);
  r0.w = max(0, r0.w);
  r3.w = max(0, r3.w);
  r2.x = dot(r2.zxy, r0.xyz);
  r2.y = 1 + -r2.x;
  r2.y = max(0.00100000005, r2.y);
  r2.y = log2(r2.y);
  r2.y = cb3[10].x * r2.y;
  r2.y = exp2(r2.y);
  r10.xyz = float3(1,1,1) + -r4.xyz;
  r4.xyz = cb3[7].yyy * r10.xyz + r4.xyz;
  r4.xyz = saturate(cb3[7].xxx * r4.xyz);
  r4.xyz = r4.xyz * r2.yyy;
  r1.x = r3.w * r1.x;
  r10.xyz = cb2[1].xyz * r1.xxx;
  r4.xyz = r4.xyz * cb3[10].yyy + r6.xyz;
  r1.x = r4.w * 0.25 + 0.25;
  r11.xyz = r9.xyz * r0.xyz;
  r0.xyz = r0.zxy * r9.yzx + -r11.xyz;
  r0.x = dot(r0.xyz, r0.xyz);
  r0.y = r4.w * r4.w;
  r0.z = r0.w * r0.y;
  r0.x = r0.z * r0.z + r0.x;
  r0.x = r0.y / r0.x;
  r0.x = r0.x * r0.x;
  r0.x = min(65504, r0.x);
  r0.x = r1.x * r0.x;
  r0.x = min(cb3[12].x, r0.x);
  r0.xyz = r7.xyz * r0.xxx + r4.xyz;
  r0.xyz = r10.xyz * r0.xyz + r8.xyz;
  r2.yz = cb1[9].xy * v1.yy;
  r2.yz = v1.xx * cb1[8].xy + r2.yz;
  r2.yz = v1.zz * cb1[10].xy + r2.yz;
  r0.w = dot(r2.yz, r2.yz);
  r0.w = sqrt(r0.w);
  r0.w = 0.00100000005 + r0.w;
  r2.yz = r2.yz / r0.ww;
  r0.w = dot(cb0[31].xy, r2.yz);
  r0.w = -cb0[31].w + r0.w;
  r1.x = cb0[32].z + -cb0[32].y;
  r0.w = r0.w * cb0[32].x + -cb0[32].y;
  r1.x = 1 / r1.x;
  r0.w = saturate(r1.x * r0.w);
  r1.x = r0.w * -2 + 3;
  r0.w = r0.w * r0.w;
  r0.w = r1.x * r0.w;
  r0.w = cb3[10].w * r0.w;
  r2.xw = saturate(r2.xw);
  r1.x = 1 + -r2.x;
  r1.x = log2(r1.x);
  r1.x = cb0[31].z * r1.x;
  r1.x = exp2(r1.x);
  r0.w = r1.x * r0.w;
  r0.w = cb0[29].z * r0.w;
  r0.xyz = r0.www * cb0[30].xyz + r0.xyz;
  r0.w = max(9.99999997e-007, r2.w);
  r0.w = log2(r0.w);
  r0.w = -r0.w * 1.20000005 + 1;
  r1.x = -1 + cb1[177].w;
  r0.w = r1.x + -r0.w;
  r2.xyzw = t4.SampleLevel(s4_s, r3.xyz, r0.w).xyzw;
  r0.w = 16 * r2.w;
  r2.xyz = r2.xyz * r0.www;
  r2.xyz = r2.xyz * r2.xyz;
  r2.xyz = cb0[37].xxx * r2.xyz;
  r3.xyz = r2.xyz * r1.www;
  r4.xyzw = t5.SampleLevel(s5_s, r1.yz, 0).xyzw;
  r1.xyz = -r2.xyz * r1.www + r4.xyz;
  r1.xyz = r4.www * r1.xyz + r3.xyz;
  r0.xyz = r1.xyz * r7.xyz + r0.xyz;
  r0.xyz = r0.xyz + r5.xyz;
  r0.w = cmp(cb1[172].w >= 0.5);
  r0.w = r0.w ? 1.000000 : 0;
  r1.xyzw = float4(-0,-0,-0,-1) + v6.xyzw;
  r1.xyzw = r0.wwww * r1.xyzw + float4(0,0,0,1);
  r2.xyz = r7.xyz + r6.xyz;
  r2.xyz = r2.xyz + -r0.xyz;
  r0.xyz = cb1[164].www * r2.xyz + r0.xyz;
  o0.xyz = r0.xyz * r1.www + r1.xyz;
  o0.w = min(65504, v7.w);
  return;
}
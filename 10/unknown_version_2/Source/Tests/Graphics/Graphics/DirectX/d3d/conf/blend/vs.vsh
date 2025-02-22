struct VSIn
{
	float2 pos : pos;
	uint vertNum : vertNum;
};

struct VSOut
{
	float4 pos : SV_Position;
	float4 col0 : color0;
	float4 col1 : color1;
};

cbuffer cb0 : register(b0)
{
	float4 inverseViewport;
};

cbuffer cb1 : register(b1)
{
	float4 vertColors[8];
};

VSOut main(VSIn input)
{
	VSOut output;
	
	output.pos = float4( 0, 0, 0, 1.0 );
	output.pos.xy = input.pos * inverseViewport.zw + inverseViewport.xy;
	
	output.col0 = vertColors[input.vertNum];
	output.col1 = vertColors[4+input.vertNum];

	return output;
}

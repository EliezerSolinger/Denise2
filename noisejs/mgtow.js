var seeds={};
const world_cordinate_bias=100000;
const default_params={
  scale:20,
  //low_bias:0,
  //high_bias:1,
  octaves:1,
};
function pnoise(x, y, z,params,seed) {
	x+=world_cordinate_bias;
	y+=world_cordinate_bias;
	if(params.offset) {
		x+=params.offset[0];
		y+=params.offset[1];
	}
	if(params.flip) {
		let _y=y;
		y=x;
		x=_y;
	}
	x=Math.abs(x);
	y=Math.abs(y);
	if(params.seed) seed=params.seed;
	if(!seed) seed=1337;
	if(!seeds[seed]) {
		seeds[seed] = new PerlinNoiseGenerator();
		seeds[seed].setSeed(seed);
	} 
	perlin=seeds[seed];
	for(let i in default_params){
	  if(params[i]==undefined) params[i]=default_params[i];
	}
  
	let scale=1/params.scale;
	//let low_bias=params.low_bias;
	//let high_bias=params.high_bias;
	let octaves=params.octaves;
  
	let h=perlin.noise(x*scale, y*scale, z*scale);// desbravanoise2f(x/scale,y/scale,1)*255;perlin.noise(x/scale, y/scale, 2)*255;
	for(let i=1;i<=octaves-1;i++){
	  let pw=[1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768][i];
	  let factor=1/pw;
	  let sc=scale*factor;
	 // h+=perlin.noise((x*sc)+pw, (y*sc)+pw, (z*sc)+pw);
	  
	  h+=(noise.perlin2((x*sc)+pw, (y*sc)+pw)+1)/2;
	  h/=2;
	}
	//if(h<low_bias) h=0;
	//if(h>high_bias) h=0;
	return h;  
  }
  
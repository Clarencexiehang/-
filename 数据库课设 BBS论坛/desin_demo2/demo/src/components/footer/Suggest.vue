<template>
	<div id="sugget_div">
		<div id="title">
			<h1>您的宝贵建议是我们的动力</h1>
		</div>
		<div id="form_div">
			<form>
				<div>
					<div>留下你的电话吧，便于给您回复 !</div>
					<input id="phone" type="text" placeholder="输入手机号" v-model="phone">
				</div>
				<div>
					<div>也可以留邮箱哦 </div>
					<input id="email" type="text" placeholder="输入邮箱" v-model="email">
				</div>
				<div>
					<div>我的建议:</div>
					<textarea id="sugget_area" cols="60" rows="10" placeholder="我的建议" v-model="sug"></textarea>
				</div>
				<input type="button" id="ok" value="发出我的建议" @click="sendSuggest">
				
			</form>
		</div>
	</div>
</template>

<script>
	export default{
		name:'Quest',
		data() {
			return{
				phone:'',
				email:'',
				sug:''
			}
		},
		methods:{
			sendSuggest(){
				if(!this.phone||!this.email||!this.sug){
					alert('请填写完整后再提交 ！');
				}else{
					var preg=new RegExp('^1[0-9]{10}');
					if(!(preg.test(this.phone))){
						alert('手机格式不正确,请重新输入 !');
					}else{
						alert('已向客服发送我的建议 !');
						this.phone='';
						this.email='';
						this.sug='';
					}
				}
			}
		}
	}
</script>

<style scoped>
	#sugget_div{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 100%;
		/* background-color: steelblue; */
	}
	h1{
		font-family: '幼圆';
	}
	form{
		width: 100%;
	}
	form>div>div,form>div>input,form>div>textarea{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		margin-left: 0;
		margin-top: 3%;
	}
	#form_div{
		width: 40%;
		margin-top: 5%;
	}
	input{
		width: 60%;
		height: 26px;
		border: none;
		border-radius: 0.3rem 0.3rem;
		border-bottom: 0.125rem solid purple;
	}
	#sugget_area{
		font-size: 20px;
		border-radius: 0.5rem 0.5rem;
	}
	#ok{
		margin-top: 4%;
		height: 2.1875rem;
		background-color: royalblue;
		font-size: 1.25rem;
		color: white;
	}
	#ok:hover{
		background-color: red;
	}
</style>
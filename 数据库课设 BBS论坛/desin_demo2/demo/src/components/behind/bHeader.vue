<template>
	<div class="head">
		<span>BBS 论坛后台管理系统</span>
		<button @click="ExitMag">退出管理</button>
	</div>
</template>

<script>
	export default{
		name:'bHeader',
		data() {
			return{
				
			}
		},
		methods:{
			ExitMag(){
				this.$router.replace({
					path:'/log'
				})
			}
		}
	}
</script>
	
<style scoped>
	.head{
		position: relative;
		
		display: flex;
		flex-direction: column;
		align-content: center;
		align-items: center;

		height: 6%;
		background-color: white;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
		
	}
	span{
		display: flex;
		flex-direction: column;
		align-content: center;
		align-items: center;
		
		width: 50%;
		height: 100%;
		
		font-size: 2.5rem;
		font-family: '幼圆';
	}
	button{
		width: 100px;
		height: 80%;
		border-radius: 0.3125rem 0.3125rem;
		position: absolute;
		right: 5%;
		background-color: royalblue;
		color: white;
		font-size: 1.25rem;
	}
</style>
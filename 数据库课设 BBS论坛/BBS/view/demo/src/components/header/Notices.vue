<template>
	<div class="not">
		<div class="sys">系统通知</div>
		<div v-for="(item,index) in notices" class="nitem">
			<div class="con">{{ item.content }}</div>
			<hr>
			<div class="time">发布于 {{ item.time }}</div>
		</div>
	</div>
</template>

<script>
import axios from 'axios'
	export default{
		name:'Notices',
		data() {
			return{
				notices:[
				]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/getannounc',
				method:'get'
			}).then((response)=>{				
				var ann=response.data.ann;
				for(var i=0;i<ann.length;i++){
					var an={
						content:ann[i].content,
						time:ann[i].posttime
					}
					this.notices.push(an);
				}
				
			}).catch((error)=>{
				
			})
		}
	}
</script>

<style scoped>
	.not{
		position: relative;
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		margin-top: 100px;
		width: 50%;
		height: 100%;
		overflow: auto;
		background-color: white;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.sys{
		position: fixed;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		height: 50px;
		background-color: royalblue;
		top: 70px;
		width: 50%;
		border-radius: 5px 5px;
		
		color: white;
		font-size: 20px;
	}
	.nitem{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: flex-start;
		
		padding: 0.625rem;
		width: 90%;
		height: auto;
		margin-top: 1.625rem;
		border-radius: 0.3125rem 0.3125rem;
		background-color: cadetblue;
	}
	.time{
		color: gray;
	}
</style>
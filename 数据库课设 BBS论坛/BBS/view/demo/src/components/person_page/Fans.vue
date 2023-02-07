<template>
	<div class="fans_item">
		<div class="care_data" v-for="(use,index) in careUser" :key="index" @click="enterUser($event,use)">
			<div class="use_info">
				<span class="head">
					<img src="../../assets/icon/head.png" class="head_img" alt="用户头像">
				</span>
				<span class="nickname">{{ use }}</span>
			</div>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	 
	export default{
		name:'Fans',
		data() {
		   return {
			   careUser:''
		   }	
		},
		methods:{
			enterUser($event,use){
				this.$router.push({
					name:'userarts',
					query:{
						nickname:use
					}
				})
			}
		},
		mounted() {
			axios({
				url:'http://127.0.0.1:5000/user/careme',
				method:'post',
				data:{
					acountname:window.sessionStorage.getItem('acountname')
				}
			}).then((response)=>{
				console.log(response);
				
				this.careUser=response.data.careUser;
				
				console.log(this.careUser);
				
			}).catch(function(error){
			
			})
			pubsub.publish('clickIndex',2);
		}
		
	}
</script>

<style scoped>
	.fans_item{
		width: 70%;
		height: 100%;
		overflow-y: auto;
		overflow: scroll;
	}
	.fan_info{
		width: 98%;
		height: 15.125rem;
		margin-top: 0.625rem;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	.care_data{
		width: 98%;
		height: 3.125rem;
		margin-top: 0.625rem;
		background-color: rgb(95, 158, 160);
		border: 1.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	
	.use_info{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
	
		height: 2.5rem;
	}
	.head{
		float: left;
		width: 2.5rem;
		height: 2.5rem;
		border-radius: 50% 50%;
	}
	.nickname{
		float: left;
	}
	.head_img{
		width: 100%;
	}
</style>
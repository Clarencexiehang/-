<template>
	<div class="info">
		<table border="1" cellspacing="0px">
			<thead>
				<th>用户名</th>
				<th>操作</th>
			</thead>
			<tbody>
				<tr v-for="(item,index) in users">
					<td class="inf" @click="LookInfo(index,item.nickname)">{{ item.nickname }}</td>
					<td class="op">
						<button @click="Cancel(index,item.nickname)">注销</button>
					</td>
				</tr>
			</tbody>
		</table>
	</div>
</template>

<script>
	import axios from 'axios'
	
	export default{
		name:'UserInfo',
		data() {
			return{
			   users:[
			   ]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/admin/getusers',
				method:'get'
			}).then((response)=>{
				var users=response.data.users;
				console.log('user ------------- ',users);
				for(var i=0;i<users.length;i++){
					var u={
						nickname:users[i]
					}
					this.users.push(u);
				}
			}).catch((error)=>{
				
			})
		},
		methods:{
			LookInfo(index,nickname){
				console.log('点击了 ',index,'  ',nickname);
				this.$bus.$emit("getNickname",nickname);
			},
			Cancel(index,nickname){
				console.log('注销用户    ',nickname);
				
				// 前端销户
				this.users.splice(index,1);
				
				// 后端数据库销户
				axios({ 
					url:'http://127.0.0.1:5000/admin/logout',
					method:'post',
					data:{
						type:'disc',
						nickname:nickname
					}
				}).then((response)=>{
					if(response.data.status=='ok'){
						alert('已成功注销用户 !');
					}
				}).catch((error)=>{
					
				})
			}
		}
	}
</script>

<style scoped>
	.info{
		flex: 2;
		height: 100%;
		
		overflow: auto;
		
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		background-color: white;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	table{
		margin-top: 1.25rem;
		width: 90%;
	}
	thead{
		height: 2.5rem;
		background-color: orange;
	}
	td{
		height: 1.875rem;
	}
	tr :hover{
		background-color: royalblue;
	}
	button{
		width: 80%;
		height: 90%;
		background-color: red;
		
		color: white;
		font-size: 1.125rem;
	}
</style>
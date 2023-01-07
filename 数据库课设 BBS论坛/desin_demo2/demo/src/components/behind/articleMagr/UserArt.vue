<template>
	<div class="uart">
		<span class="left">
			<table border="1" cellspacing="0px">
				<tbody>
					<tr v-for="(item,index) in users" :id="'t'+index" @click="ClickTd(index)">
						<td class="inf">{{ item.nickname }}</td>
					</tr>
				</tbody>
			</table>
		</span>
		<span class="right">
			<router-view></router-view>
		</span>
	</div>
</template>

<script>
	import axios from 'axios'
	import $ from 'jquery'
	export default{
		name:'UserArt',
		data() {
			return{
				users:[]
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
			ClickTd(index){
				console.log('***********点击了 ：',index,' ',this.users[index].nickname);
				var cid='t'+index;
				$('#'+cid).addClass("useTdbc");
				for(var i=0;i<this.users.length;i++){
					if(i!=index){
						var tid='t'+i;
						$('#'+tid).removeClass("useTdbc");
					}
				}
				
				this.$bus.$emit("Nickname",this.users[index].nickname);
				this.$router.push({
					name:'userartdetail'
				})
			}
		}
	}
</script>

<style scoped>
	.uart{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 100%;
		background-color: white;
		
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.left{
		flex: 1;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		height: 100%;
		overflow: auto;
	}
	table{
		width: 100%;
		height: auto;
	}
	td{
		width: 100%;
		height: 40px;
	}
	.useTdbc{
		background-color: orange;
	}
	.right{
		flex: 5;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		height: 100%;
	}
</style>
<template>
	<div class="rdt">
		<table border="1" cellspacing="0px">
			<tbody @click="TdClick($event)">
				<tr>
					<td id="t1">
						<router-link :to="{name:'userregiternum'}" id="a1">用户数据</router-link>
					</td>
				</tr>
				<tr>
					<td id="t2">
						<router-link :to="{name:'hotuser'}" id="a2">今日活跃用户</router-link>
					</td>
				</tr>
			</tbody>
		</table>
	</div>
</template>

<script>
	import $ from 'jquery'
	
	export default{
		name:'RunDataItem',
		data() {
			return{}
		},
		methods: {
			TdClick(e){
				var s=e.target.id;
				console.log(s);
				if(s=="a1"){
					$("#a1").addClass("sStyleBor");
					$("#a2").removeClass("sStyleBor");
				}else if(s=="a2"){
					$("#a2").addClass("sStyleBor");
					$("#a1").removeClass("sStyleBor");
				}
			}
		}
	}
</script>

<style scoped>
	.sStyleBor{
		background-color: orange;
	}
	.rdt{
		flex: 2;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		height: 100%;
	}
	table{
		width: 100%;
		height: auto;
	}
	td{
		height: 30px;
	}
	a{
		display: block;
		text-decoration: none;
		width: 100%;
		height: 100%;
		color: royalblue;
		font-size: 20px;
	}
	
</style>
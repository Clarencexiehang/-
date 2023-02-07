<template>
	<div id="content">
		<span id="concat">
			<i class="el-icon-phone">联系我们 :</i>&nbsp;&nbsp;&nbsp;
			<router-link to="/main/">phone:111-2343</router-link>&nbsp;&nbsp;
			<router-link to="/main/">email:dsgd@123.com</router-link>
		</span>
		<span id="question">
			<i class="el-icon-question">有疑问:</i>&nbsp;&nbsp;
			<router-link :to="{name:'ask'}">咨询</router-link>
		</span>
		<span id="quest">
			<i class="el-icon-info">提出建议</i>&nbsp;&nbsp;
			<router-link :to="{name:'suggest'}">去提建议</router-link>
		</span>
	</div>
</template>

<script>
	export default{
		name:'MainFooter',
		data() {
			return{
			}
		}
	}
</script>

<style scoped>
	#content{
		position: absolute;
		bottom: 0;
		display: flex;
		flex-direction: row;
		justify-content: space-evenly;
		align-items: center;
		
		width: 100%;
		height: 6%;
		background-color: transparent;
	}
	i{
		font-size: 15px;
	}
	a{
		text-decoration: none;
		color: royalblue;
	}
	#concat,#quest,#suggest{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		height: 100%;
	}
</style>
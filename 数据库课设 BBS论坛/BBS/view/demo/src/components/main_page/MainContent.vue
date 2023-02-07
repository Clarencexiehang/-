<template>
	<div id="content">
		<span id="back">
			<i class="el-icon-back" @click="back"></i>
		</span>
		<router-view></router-view>
	</div>
</template>

<script>
	export default{
		name:'MainContent',
		data() {
			return{
				
			}
		},
		methods: {
		  handleOpen(key, keyPath) {
			console.log(key, keyPath);
		  },
		  handleClose(key, keyPath) {
			console.log(key, keyPath);
		  },
		  back(){
			  this.$router.back();
		  }
		}
	}
</script>

<style scoped>
	#content{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		height: 88%;
		/* background-image: url('../../assets/backimg/blu.jpg'); */
		background-repeat: no-repeat;
		margin-top: 5px;
	}
	#back{
		position: absolute;
		left: 10%;
		top: 20px;
	}
	#back i{
		font-size: 25px;
		color: blue;
	}
</style>